/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_rtutrans.h"

Z_RtuTrans::Z_RtuTrans()
{
    mSerial = NULL;
    isRun = false;
    mSentBuf = (uchar *)malloc(2*SERIAL_LEN);
    mRecvBuf = (uchar *)malloc(2*SERIAL_LEN);
    mMutex = new QMutex();

    mRtuPkt = new  Z_sRtuRecv();
    mRtuSent = new Z_RtuSent();
    mRtuRecv = new Z_RtuRecv();
}


Z_RtuTrans *Z_RtuTrans::bulid()
{
    static Z_RtuTrans* sington = NULL;
    if(sington == NULL) {
        sington = new Z_RtuTrans();
    }
    return sington;
}


/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void Z_RtuTrans::init(SerialPort *serial)
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
bool Z_RtuTrans::sentSetCmd(int addr, int reg, ushort value, int msecs)
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
                qDebug() << "Z sent Set Cmd Err";
        }
    }

    return ret;
}

void Z_RtuTrans::getAlarm(sDataUnit &data)
{
    if((data.value < data.min) || (data.value > data.max)) {
        if(data.alarm == 0)
            data.alarm = 1;
    } else {
        data.alarm = 0;
    }

    if((data.value < data.crMin) || (data.value > data.crMax)) {
        if(data.crAlarm == 0)
            data.crAlarm = 1;
    } else {
        data.crAlarm = 0;
    }
}

void Z_RtuTrans::dataUnit(int i, Z_sDataUnit &rtu, sDataUnit &data)
{
    data.value = rtu.value[i];
    data.min = rtu.min[i];
    data.max = rtu.max[i];

    data.crMin = rtu.crMin[i];
    data.crMax = rtu.crMax[i];
    data.crAlarm = rtu.crAlarm[i];

    getAlarm(data);
}

void Z_RtuTrans::devObjData(Z_sObjData &rtuData, int i, sObjData &data)
{
    data.id = i;
    dataUnit(i, rtuData.vol, data.vol);
    dataUnit(i, rtuData.cur, data.cur);
    data.ele = rtuData.ele[i];
    data.activePow = data.vol.value * data.cur.value;
    data.pf = rtuData.pf[i];
    data.sw = rtuData.sw[i];

    if(rtuData.pow[i] > 0) {
        data.pow = rtuData.pow[i];
    } else {
        data.pow = data.activePow * data.pf / 100.0;
    }
}

void Z_RtuTrans::envData(Z_sEnv &rtuData, sEnvData &data)
{
    data.envNum = 2;

    for(int i=0; i<data.envNum; ++i) {
        dataUnit(i, rtuData.tem, data.tem[i]);
        dataUnit(i, rtuData.hum, data.hum[i]);

        data.door[i] = rtuData.door[i];
        data.water[i] = rtuData.water[i];
        data.smoke[i] = rtuData.smoke[i];
    }
}

void Z_RtuTrans::devData(Z_sRtuPacket &rtuData, sDevData &data)
{
    int num = data.lineNum = rtuData.line.num;
    for(int i=0; i<num; ++i) {
        devObjData(rtuData.line, i, data.line[i]);
    }

    num = data.loopNum = rtuData.loop.num;
    for(int i=0; i<num; ++i) {
        devObjData(rtuData.loop, i, data.loop[i]);
    }

    num = data.outputNum = rtuData.output.num;
    for(int i=0; i<num; ++i) {
        devObjData(rtuData.output, i, data.output[i]);
    }

    envData(rtuData.env, data.env);
}

void Z_RtuTrans::devDataPacket(Z_sRtuRecv *pkt, sDataPacket *packet)
{
    packet->id = pkt->addr;
    packet->offLine = pkt->offLine;
    packet->br = pkt->data.br;
    packet->version = pkt->data.version;
    packet->devSpec = pkt->data.devSpec;
    strcpy(packet->ip, pkt->data.ip);
    strcpy(packet->mac, pkt->data.mac);

    devData(pkt->data, packet->data);
}


/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int Z_RtuTrans::transData(int addr, ushort reg, ushort len, Z_sRtuRecv *pkt, int msecs)
{
    uchar offLine = 0;
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, reg, len, sent); // 把数据打包成通讯格式的数据
    if(mSerial) {
        rtn = mRecvLen = mSerial->transmit(sent, rtn, recv, msecs); // 传输数据，发送同时接收
    } else rtn = 0;

    if(rtn > 0)
    {
        bool ret = mRtuRecv->recvPacket(recv, rtn, reg, pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
            }
        }
    }
    pkt->offLine = offLine;

    return offLine;
}


int Z_RtuTrans::transData(int addr, int cmd, sDataPacket *pkt, int msecs)
{
    static ushort array[Z_RtuReg_CmdNum][2] = {
        Z_RtuReg_DevType,       Z_RtuReg_DevTypeSize,
        Z_RtuReg_DevIP,         Z_RtuReg_DevIPSize,
        Z_RtuReg_DevMac,        Z_RtuReg_DevMacSize,
        Z_RtuReg_OutputNum,     Z_RtuReg_OutputNumSize,
        Z_RtuReg_OutputSw,      Z_RtuReg_OutputSwSize,

        Z_RtuReg_LineCur,        Z_RtuReg_LineCurSize,
        Z_RtuReg_LineCurMin,     Z_RtuReg_LineCurMinSize,
        Z_RtuReg_LineCurMax,     Z_RtuReg_LineCurMaxSize,
        Z_RtuReg_LineCurCrMin,   Z_RtuReg_LineCurCrMinSize,
        Z_RtuReg_LineCurCrMax,   Z_RtuReg_LineCurCrMaxSize,

        Z_RtuReg_LineVol,        Z_RtuReg_LineVolSize,
        Z_RtuReg_LineVolMin,        Z_RtuReg_LineVolMinSize,
        Z_RtuReg_LineVolMax,        Z_RtuReg_LineVolMaxSize,
        Z_RtuReg_LineVolCrMin,        Z_RtuReg_LineVolCrMinSize,
        Z_RtuReg_LineVolCrMax,        Z_RtuReg_LineVolCrMaxSize,

        Z_RtuReg_LinePow ,        Z_RtuReg_LinePowSize,
        Z_RtuReg_LinePF ,        Z_RtuReg_LinePFSize,
        Z_RtuReg_LineEle ,        Z_RtuReg_LineEleSize,

        Z_RtuReg_LoopCur ,        Z_RtuReg_LoopCurSize ,
        Z_RtuReg_LoopCurMin ,        Z_RtuReg_LoopCurMinSize ,
        Z_RtuReg_LoopCurMax ,        Z_RtuReg_LoopCurMaxSize ,
        Z_RtuReg_LoopCurCrMin ,        Z_RtuReg_LoopCurCrMinSize ,
        Z_RtuReg_LoopCurCrMax ,        Z_RtuReg_LoopCurCrMaxSize ,

        Z_RtuReg_LoopVol ,        Z_RtuReg_LoopVolSize ,
        Z_RtuReg_LoopEle ,        Z_RtuReg_LoopEleSize ,

        Z_RtuReg_OutputCur ,        Z_RtuReg_OutputCurSize ,
        Z_RtuReg_OutputCurMin ,        Z_RtuReg_OutputCurMinSize ,
        Z_RtuReg_OutputCurMax ,        Z_RtuReg_OutputCurMaxSize ,
        Z_RtuReg_OutputCurCrMin ,        Z_RtuReg_OutputCurCrMinSize ,
        Z_RtuReg_OutputCurCrMax ,        Z_RtuReg_OutputCurCrMaxSize ,
        Z_RtuReg_OutputPF ,        Z_RtuReg_OutputPFSize ,
        Z_RtuReg_OutputEle ,        Z_RtuReg_OutputEleSize ,

        Z_RtuReg_TemData ,        Z_RtuReg_TemSize ,
        Z_RtuReg_TemMin ,        Z_RtuReg_TemMinSize ,
        Z_RtuReg_TemMax ,        Z_RtuReg_TemMaxSize ,
        Z_RtuReg_TemCrMin ,        Z_RtuReg_TemCrMinSize ,
        Z_RtuReg_TemCrMax ,        Z_RtuReg_TemCrMaxSize ,

        Z_RtuReg_HumData ,        Z_RtuReg_HumSize ,
        Z_RtuReg_HumMin ,        Z_RtuReg_HumMinSize ,
        Z_RtuReg_HumMax ,        Z_RtuReg_HumMaxSize,
        Z_RtuReg_HumCrMin ,        Z_RtuReg_HumCrMinSize ,
        Z_RtuReg_HumCrMax ,        Z_RtuReg_HumCrMaxSize ,

        Z_RtuReg_DoorData ,        Z_RtuReg_DoorSize ,
        Z_RtuReg_WaterData ,        Z_RtuReg_WaterSize ,
        Z_RtuReg_SmokeData ,        Z_RtuReg_SmokeSize ,
    };

    int ret = transData(addr, array[cmd][0], array[cmd][1], mRtuPkt, msecs);
    if(ret)  devDataPacket(mRtuPkt, pkt);
    else pkt->id = addr;

    return ret;
}


QByteArray Z_RtuTrans::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > SERIAL_LEN))  mSentLen = SERIAL_LEN;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}

QByteArray Z_RtuTrans::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > SERIAL_LEN))  mRecvLen = SERIAL_LEN;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}
