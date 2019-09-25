/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_rtutrans.h"

IP_RtuTrans::IP_RtuTrans()
{
    mSerial = NULL;
    isRun = false;
    mSentBuf = (uchar *)malloc(2*SERIAL_LEN);
    mRecvBuf = (uchar *)malloc(2*SERIAL_LEN);
    mMutex = new QMutex();

    mRtuPkt = new  IP_Rtu_Recv();
    mRtuSent = new IP_RtuSent();
    mRtuRecv = new IP_RtuRecv();
}


IP_RtuTrans *IP_RtuTrans::bulid()
{
    static IP_RtuTrans* sington = NULL;
    if(sington == NULL) {
        sington = new IP_RtuTrans();
    }
    return sington;
}

/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void IP_RtuTrans::init(SerialPort *serial)
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
bool IP_RtuTrans::sentSetCmd(int addr, int reg, ushort value, int msecs)
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
                qDebug() << "IP sent Set Cmd Err";
        }
    }

    return ret;
}


void IP_RtuTrans::dataUnit(int i, IP_sDataUnit &rtu, sDataUnit &data)
{
    data.value = rtu.value[i];
    data.min = rtu.min[i];
    data.max = rtu.max[i];
    data.alarm = rtu.alarm[i];
}

void IP_RtuTrans::devLine(IP_RtuRecvLine &rtuData, sDevData &data)
{
    data.lineNum = rtuData.lineNum;

    for(int i=0; i<data.lineNum; ++i) {
        data.line[i].id = i;
        dataUnit(i, rtuData.vol, data.line[i].vol);
        dataUnit(i, rtuData.cur, data.line[i].cur);
        data.line[i].ele = rtuData.ele[i];
        data.line[i].pow = rtuData.pow[i];
        data.line[i].activePow = rtuData.activePow[i];
        data.line[i].pf = rtuData.pf[i];
        data.line[i].sw = rtuData.sw[i];        
    }
}

void IP_RtuTrans::envData(IP_RtuRecvLine &rtuData, sEnvData &data)
{
    data.envNum = 1;

    for(int i=0; i<data.envNum; ++i) {
        dataUnit(i, rtuData.tem, data.tem[i]);
        dataUnit(i, rtuData.hum, data.hum[i]);
    }
}

void IP_RtuTrans::devData(IP_Rtu_Recv *pkt, sDataPacket *packet)
{
    packet->id = pkt->addr;
    packet->offLine = pkt->offLine;
    packet->br = pkt->data.br;
    packet->version = pkt->data.version;

    devLine(pkt->data, packet->data);
    envData(pkt->data, packet->data.env);
}


/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int IP_RtuTrans::transData(int addr, int line, sDataPacket *pkt, int msecs)
{
    uchar offLine = 0;
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, line,sent); // 把数据打包成通讯格式的数据
    if(mSerial) {
        rtn = mRecvLen = mSerial->transmit(sent, rtn, recv, msecs); // 传输数据，发送同时接收
    } else rtn = 0;

    if(rtn > 0)
    {
        bool ret = mRtuRecv->recvPacket(recv, rtn, mRtuPkt); // 解释数据
        if(ret) {
            if(addr == mRtuPkt->addr) {
                offLine = 1;
                devData(mRtuPkt, pkt);
            }
        }
    }
    pkt->offLine = offLine;
    if(!offLine) pkt->id = addr;

    return offLine;
}

QByteArray IP_RtuTrans::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > SERIAL_LEN))  mSentLen = SERIAL_LEN;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}



QByteArray IP_RtuTrans::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > SERIAL_LEN))  mRecvLen = SERIAL_LEN;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}
