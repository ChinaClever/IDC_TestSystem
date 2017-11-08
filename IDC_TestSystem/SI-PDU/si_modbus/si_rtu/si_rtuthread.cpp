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
    mRtuPkt = new SI_Rtu_Recv();
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
    if(!isRun) {
        QTimer::singleShot(100,this,SLOT(start()));  // 启动线程
    }
}


/**
 * @brief 发送设置命令
 * @param addr 地址
 * @param reg 寄存吕
 * @param value 值
 * @return true
 */
bool SI_RtuThread::sentSetCmd(uchar addr, uchar reg, ushort value)
{
    bool ret = false;
    static uchar buf[RTU_BUF_SIZE] = {0};
    QMutexLocker locker(mMutex);

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, mBuf);
        if(len == rtn) {
            if(memcmp(buf, mBuf,rtn) == 0)
                ret = true;
            else
                qDebug() << "SI sent Set Cmd Err";
        }
    }

    return ret;
}



void SI_RtuThread::transData(int addr, int line)
{
    char offLine = 0;
    uchar *buf = mBuf;
    SI_Rtu_Recv *pkt = mRtuPkt;
    //    sBoxData *box = &(mBusData->box[addr]);

    int rtn = mRtuSent->sentDataBuff(addr,line, buf); // 把数据打包成通讯格式的数据
    rtn = mSerial->transmit(buf, rtn, buf); // 传输数据，发送同时接收
    if(rtn > 0) {
        bool ret = mRtuRecv->recvPacket(buf, rtn, pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
                //                loopData(box, pkt);
                //                envData(&(box->env), pkt);
                //                box->rate = pkt->rate;
            }
        }
    }
    //    box->offLine = offLine;
}



void SI_RtuThread::run()
{
    isRun = true;
    while(isRun)
    {

        for(int i=1; i<2; ++i)
        {
            QMutexLocker locker(mMutex);
            transData(i, 1);
            msleep(10);
        }

        msleep(100);
    }
}
