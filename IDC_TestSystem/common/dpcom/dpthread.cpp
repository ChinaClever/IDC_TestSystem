#include "dpthread.h"

DpThread::DpThread(QObject *parent) : QThread(parent)
{
    mCount = 0;
    isSave = isRun = false;
    mRwLock = new QReadWriteLock();

    mEnv = nullptr;
    mLine = nullptr;
    mTrans = nullptr;
    mAlarmSlave = nullptr;
    mLineThreshold = nullptr;

    timer = new QTimer(this);
    timer->start(60*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


DpThread::~DpThread()
{
    isRun = false;
    wait();
}

void DpThread::saveModbusCmd(QStringList &list)
{
    DbModbusCmdItem item;
    item.dev_id = list.at(0).toInt();

    QWriteLocker locker(mRwLock); // 正在操作时不允许关闭
    insertItem(item);
    msleep(30);
}

void DpThread::workDone()
{
    if(mAlarmSlave)  mAlarmSlave->run();

    if(isSave)
    {
        isSave = false;
        if(mEnv) mEnv->run();
        if(mLine) mLine->run();
        if(mTrans) mTrans->run();
        if(mLineThreshold) mLineThreshold->run();
    }
}

void DpThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

        QWriteLocker locker(mRwLock); // 正在操作时不允许关闭
        workDone();
        isRun  = false;
    }
}

void DpThread::timeoutDone()
{
    int num = getTimeOut();
    if(mCount++ % num == 0) {
        if(getStart())
            isSave = true;
        else
            mCount = 1;
    }

}

void DpThread::initPackets(sDevPackets *packets)
{
    mEnv->initPackets(packets);
    mLine->initPackets(packets);
    mTrans->initPackets(packets);
    mAlarmSlave->initPackets(packets);
    mLineThreshold->initPackets(packets);
}
