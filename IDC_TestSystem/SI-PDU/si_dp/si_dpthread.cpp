/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_dpthread.h"
#include "si_sql/sidbmodbuscmd.h"

SI_DpThread::SI_DpThread(QObject *parent) : QThread(parent)
{
    mCount = 0;
    isSave = isRun = false;
    mRwLock = new QReadWriteLock();

    mAlarmSlave = new SI_DpAlarmSave(this);
    mEnv = new SI_DpSaveEnv(this);
    mThreshold = new SI_DpSaveThreshold(this);
    mRecord = new SI_DpSaveRecord(this);
    mTrans = new SI_DpSaveTrans(this);

    timer = new QTimer(this);
    timer->start(60*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


SI_DpThread::~SI_DpThread()
{
    isRun = false;
    wait();
}

void SI_DpThread::saveModbusCmd(QStringList &list)
{
    DbModbusCmdItem item;
    item.dev_id = list.at(0).toInt();

    QWriteLocker locker(mRwLock); // 正在操作时不允许关闭
    SiDbModbusCmd::bulid()->insertItem(item);
    msleep(30);
}

void SI_DpThread::workDone()
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

void SI_DpThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

        QWriteLocker locker(mRwLock); // 正在操作时不允许关闭
        workDone();
        isRun  = false;
    }
}

void SI_DpThread::timeoutDone()
{
     SiConfigItem *item = SiConfigFile::bulid()->item;
    int num = item->logMins;
    if(mCount++ % num == 0) {
        if(item->testMode == SI_Test_Simulate)
            isSave = true;
        else
            mCount = 1;
    }

}

