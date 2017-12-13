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
    mBuf = (uchar *)malloc(RTU_BUF_SIZE);
    mMutex = new QMutex();

    mRtuSent = new SI_RtuSent();
    mRtuRecv = new SI_RtuRecv();
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
    QMutexLocker locker(mMutex);

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, mBuf, msecs);
        if(len == rtn) {
            if(memcmp(buf, mBuf,rtn) == 0)
                ret = true;
            else
                qDebug() << "SI sent Set Cmd Err";
        }
    }

    return ret;
}


/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int SI_RtuThread::transData(int addr, int line, SI_Rtu_Recv *pkt, int msecs)
{
    char offLine = 0;
    uchar *buf = mBuf;

    int rtn = mLen = mRtuSent->sentDataBuff(addr,line, buf); // 把数据打包成通讯格式的数据
    if(mSerial) {
        rtn = mSerial->transmit(buf, rtn, buf, msecs); // 传输数据，发送同时接收
    } else rtn = 0;

    if(rtn > 0)
    {
        bool ret = mRtuRecv->recvPacket(buf, rtn, pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
            }
        }
    }
    pkt->offLine = offLine;

    return offLine;
}

QByteArray SI_RtuThread::getSentCmd()
{
    QByteArray array;
    array.append((char *)mBuf, mLen);
    return array;
}
