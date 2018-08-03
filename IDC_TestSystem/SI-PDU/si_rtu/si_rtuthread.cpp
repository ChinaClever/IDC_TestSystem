/*
 * RTU线程
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_rtuthread.h"

SI_RtuThread::SI_RtuThread(QObject *parent) : QThread(parent)
{
    mSerial = NULL;
    isRun = false;
    mSentBuf = (uchar *)malloc(2*SERIAL_LEN);
    mRecvBuf = (uchar *)malloc(2*SERIAL_LEN);
    mMutex = new QMutex();

    mRtuSent = new SI_RtuSent();
    mRtuRecv = new SI_RtuRecv();
    mRtuPkt = new SI_Rtu_Recv();
}

SI_RtuThread::~SI_RtuThread()
{
    isRun = false;
    wait();
}


SI_RtuThread *SI_RtuThread::bulid(QObject *parent)
{
    static SI_RtuThread* sington = NULL;
    if(sington == NULL) {
        sington = new SI_RtuThread(parent);
    }
    return sington;
}

/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void SI_RtuThread::init(SerialPort *serial)
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
bool SI_RtuThread::sentSetCmd(int addr, int reg, ushort value, int msecs)
{
    bool ret = false;
    static uchar buf[RTU_BUF_SIZE] = {0};
    uchar *sent = mSentBuf;
    QMutexLocker locker(mMutex);

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, sent, msecs);
        if(len == rtn) {
            if(memcmp(buf, sent,rtn) == 0)
                ret = true;
            else
                qDebug() << "SI sent Set Cmd Err";
        }
    }

    return ret;
}

void SI_RtuThread::dataUnit(int i, SI_sDataUnit &rtu, sDataUnit &data)
{
    data.value = rtu.value[i];
    data.min = rtu.min[i];
    data.max = rtu.max[i];
    data.alarm = rtu.alarm[i];
}

void SI_RtuThread::devLine(SI_RtuRecvLine &rtuData, sDevData &data)
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

void SI_RtuThread::envData(SI_RtuRecvLine &rtuData, sEnvData &data)
{
    data.envNum = 1;

    for(int i=0; i<data.envNum; ++i) {
        dataUnit(i, rtuData.tem, data.tem[i]);
        dataUnit(i, rtuData.hum, data.hum[i]);
    }
}

void SI_RtuThread::devData(SI_Rtu_Recv *pkt, sDataPacket *packet)
{
    packet->id = pkt->addr;
    packet->offLine = pkt->offLine;
    packet->br = pkt->data.br;

    devLine(pkt->data, packet->data);
    envData(pkt->data, packet->data.env);
}

int SI_RtuThread::transData(int addr, int line, SI_Rtu_Recv *pkt, int msecs)
{
    uchar offLine = 0;
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, line,sent); // 把数据打包成通讯格式的数据
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

/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int SI_RtuThread::transData(int addr, int line, sDataPacket *pkt, int msecs)
{
    int ret = transData(addr, line, mRtuPkt, msecs);
    if(ret) {
        devData(mRtuPkt, pkt);
    }

    return ret;
}


QByteArray SI_RtuThread::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > SERIAL_LEN))  mSentLen = SERIAL_LEN;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}



QByteArray SI_RtuThread::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > SERIAL_LEN))  mRecvLen = SERIAL_LEN;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}

