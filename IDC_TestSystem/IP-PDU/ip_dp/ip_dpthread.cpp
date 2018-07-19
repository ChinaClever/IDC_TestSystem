/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_dpthread.h"
#include "ip_sql/ipdbmodbuscmd.h"


IP_DpThread::IP_DpThread(QObject *parent) : QThread(parent)
{
    mCount = 0;
    isSave = isRun = false;
    mRwLock = new QReadWriteLock();

    mAlarmSlave = new IP_DpAlarmSlave(this);
    mEnv = new IP_DpSlaveEnv(this);
    mThreshold = new IP_DpSaveThreshold(this);
    mRecord = new IP_DpSlaveRecord(this);
    mTrans = new IP_DpSlaveTrans(this);

    timer = new QTimer(this);
    timer->start(60*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


IP_DpThread::~IP_DpThread()
{
    isRun = false;
    wait();
}

void IP_DpThread::saveModbusCmd(QStringList &list)
{
    IpDbModbusCmdItem item;
    item.dev_id = list.at(0).toInt();

    QWriteLocker locker(mRwLock); // 正在操作时不允许关闭
    IpDbModbusCmd::bulid()->insertItem(item);
    msleep(30);
}

void IP_DpThread::workDone()
{
    mAlarmSlave->run();

    if(isSave)
    {
        isSave = false;
        mEnv->run();
        mThreshold->run();
        mRecord->run();
        mTrans->run();
    }
}

void IP_DpThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

        QWriteLocker locker(mRwLock); // 正在操作时不允许关闭
        workDone();
        isRun  = false;
    }
}

void IP_DpThread::timeoutDone()
{
     IpConfigItem *item = IP_ConfigFile::bulid()->item;
    int num = item->logMins;
    if(mCount++ % num == 0) {
        if(item->testMode == IP_Test_Simulate)
            isSave = true;
        else
            mCount = 1;
    }

}
