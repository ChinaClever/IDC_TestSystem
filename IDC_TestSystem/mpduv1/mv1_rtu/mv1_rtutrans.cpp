/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_rtutrans.h"

MV1_RtuTrans::MV1_RtuTrans()
{
    mSerial = NULL;
    isRun = false;
    mSentBuf = (uchar *)malloc(2*SERIAL_LEN);
    mRecvBuf = (uchar *)malloc(2*SERIAL_LEN);
    mMutex = new QMutex();

    mRtuPkt = new  ZM_sRtuRecv();
    mRtuSent = new MV1_RtuSent();
    mRtuRecv = new MV1_RtuRecv();
}

MV1_RtuTrans *MV1_RtuTrans::bulid()
{
    static MV1_RtuTrans* sington = NULL;
    if(sington == NULL) {
        sington = new MV1_RtuTrans();
    }
    return sington;
}


/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void MV1_RtuTrans::init(SerialPort *serial)
{
    mSerial = serial;
}


/**
 * @brief 发送设置命令
 * @param addr 地址
 * @param reg 寄存吕
 * @param value 值
 * @return true
 */
bool MV1_RtuTrans::sentSetCmd(int addr, int reg, ushort value, int msecs)
{
    bool ret = false;
    static uchar buf[SERIAL_LEN] = {0};
    QMutexLocker locker(mMutex);
    uchar *sent = mSentBuf;

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, sent, msecs);
        if(len == rtn) {
            if(memcmp(buf, sent,rtn) == 0)
                ret = true;
            else
                qDebug() << "MV1 sent Set Cmd Err";
        }
    }

    if((reg>=1079)&&(reg<=1090)||(reg>=1099)&&(reg<=1204)||(reg>=1205)&&(reg<=1210)) {sleep(1);
        if((reg>=1079)&&(reg<=1090)||(reg>=1205)&&(reg<=1210)) {
            transData(addr, 4, mDataPkt, msecs);
        } else {
            transData(addr, 5, mDataPkt, msecs);
        }
    }



    return ret;
}

void MV1_RtuTrans::getAlarm(sDataUnit &data)
{
    if((data.value < data.min) || (data.value > data.max)) {
        if(data.alarm == 0)
            data.alarm = 1;
    } else {
        data.alarm = 0;
    }

    if((data.value < data.crMin) || (data.value > data.crMax)) {
        if(data.crMax > 0)
            data.crAlarm = 1;
    } else {
        data.crAlarm = 0;
    }
}

void MV1_RtuTrans::dataUnit(int i, ZM_sDataUnit &rtu, sDataUnit &data)
{
    data.value = rtu.value[i];
    data.min = rtu.min[i];
    data.max = rtu.max[i];

    data.crMin = rtu.crMin[i];
    data.crMax = rtu.crMax[i];
    data.crAlarm = rtu.crAlarm[i];

    getAlarm(data);
}

void MV1_RtuTrans::devObjData(ZM_sObjData &rtuData, int i, sObjData &data)
{
    data.id = i;
    dataUnit(i, rtuData.vol, data.vol);
    dataUnit(i, rtuData.cur, data.cur);
    data.ele = rtuData.ele[i];
    data.pow = rtuData.pow[i];
    data.activePow = rtuData.activePow[i];
    data.pf = rtuData.pf[i];
    data.sw = rtuData.sw[i];
}

void MV1_RtuTrans::envData(ZM_sRtuPacket &rtuData, sEnvData &data)
{
    data.envNum = 2;

    for(int i=0; i<data.envNum; ++i) {
        dataUnit(i, rtuData.env.tem, data.tem[i]);
        dataUnit(i, rtuData.env.hum, data.hum[i]);
    }
}

void MV1_RtuTrans::devData(ZM_sRtuPacket &rtuData, sDevData &data)
{
    int num = data.lineNum = rtuData.line.num;
    for(int i=0; i<num; ++i) {
        devObjData(rtuData.line, i, data.line[i]);
    }

    num = data.outputNum = 24;
    for(int i=0; i<num; ++i) {
        devObjData(rtuData.output, i, data.output[i]);
    }

    envData(rtuData, data.env);
}

void MV1_RtuTrans::devDataPacket(ZM_sRtuRecv *pkt, sDataPacket *packet)
{
    packet->id = pkt->addr;
    packet->offLine = pkt->offLine;
    packet->br = pkt->data.br;
    packet->version = pkt->data.version;
    packet->devSpec = pkt->data.devSpec;

    devData(pkt->data, packet->data);
}


/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int MV1_RtuTrans::transData(int addr, ushort reg, ushort len, ZM_sRtuRecv *pkt, int msecs)
{
    uchar offLine = 0;
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, reg, len, sent); // 把数据打包成通讯格式的数据
    if(mSerial) {
        rtn = mRecvLen = mSerial->transmit(sent, rtn, recv, msecs); // 传输数据，发送同时接收
    } else rtn = 0;

    if(rtn > 0)
    {
        bool ret = mRtuRecv->recvPacket(recv, rtn, pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
            }
        }
    }
    pkt->offLine = offLine;

    return offLine;
}

int MV1_RtuTrans::transData(int addr, int cmd, sDataPacket *pkt, int msecs)
{
    ushort reg=0, len=0;
    switch (cmd) {
    case 0: reg = MV1_RtuReg_LineData; len = MV1_RtuReg_LineSize;  break;
    case 1: reg = MV1_RtuReg_OutputData; len = MV1_RtuReg_OutputSize; break;
    case 2: reg = MV1_RtuReg_OutputEles; len = MV1_RtuReg_OutputEleSize; break;
    case 3: reg = MV1_RtuReg_EnvData; len = MV1_RtuReg_EnvSize;  break;
    case 4: reg = MV1_RtuReg_LineThresholdData; len = MV1_RtuReg_LineThresholdSize; break;
    case 5: reg = MV1_RtuReg_OutputThresholdData; len = MV1_RtuReg_OutputThresholdSize;  break;
    case 6: reg = MV1_RtuReg_LineSw; len = MV1_RtuReg_LineSwSize; break;
    case 7: reg = MV1_RtuReg_EnvThresholdData; len = MV1_RtuReg_EnvThresholdSize; break;
    case 8: reg = MV1_RtuReg_DevAddr; len = MV1_RtuReg_DevAddrSize; break;
    case 9: reg = MV1_RtuReg_LineNum; len = MV1_RtuReg_LineNumSize; break;
    case 10: reg = MV1_RtuReg_OutputSw; len = MV1_RtuReg_OutputSwSize; break;
    default: break;
    }

    int ret = transData(addr, reg, len, mRtuPkt, msecs);
    if(ret)  devDataPacket(mRtuPkt, pkt);
    else pkt->id = addr;
    mDataPkt = pkt;

    return ret;
}

QByteArray MV1_RtuTrans::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > SERIAL_LEN))  mSentLen = SERIAL_LEN;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}

QByteArray MV1_RtuTrans::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > SERIAL_LEN))  mRecvLen = SERIAL_LEN;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}

