/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mpdurtutestthread.h"

MpduRtuTestThread::MpduRtuTestThread(QObject *parent) : QThread(parent)
{
    mReg = 0;
    mSerial = NULL;
    mBuf = (uchar *)malloc(256);
    mMutex = new QMutex();

    isRun = false;
    mRtuSent = new MpduRtuTestSent();
}

MpduRtuTestThread::~MpduRtuTestThread()
{
    isRun = false;
    wait();
}


/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void MpduRtuTestThread::init(SerialPort *serial)
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
bool MpduRtuTestThread::sentSetCmd(int addr, int reg, ushort value, int msecs)
{
    bool ret = false;
    static uchar buf[256] = {0};
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

void MpduRtuTestThread::run()
{
    if(isRun == false) {
        isRun = true;

        for(int i=0; i<mList.size(); ++i)
        {
            int id = i+1;
            if(mReg) id = mList.at(i).reg - mReg+1;

            QString str = tr("输出位 %1 命令执行").arg(id);
            bool ret = sentSetCmd(mList.at(i).addr,mList.at(i).reg,mList.at(i).value, 5);
            if(ret) {
                str += tr("成功!!");
            } else {
                 str += tr("失败!!");
            }

            emit cmdSig(str);
        }

        mList.clear();
        isRun = false;
    }
}
