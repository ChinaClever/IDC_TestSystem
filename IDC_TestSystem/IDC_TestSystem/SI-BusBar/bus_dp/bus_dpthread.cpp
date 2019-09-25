/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_dpthread.h"
#include "bus_sql/busdbmodbuscmd.h"
#include "bus_com/bus_configfile.h"

BUS_DpThread::BUS_DpThread(QObject *parent) : QThread(parent)
{
    mCount = 0;
    isSave = isRun = false;
    mRwLock = new QReadWriteLock();

    mTg = new BUS_DpTg();
    mAlarm = new BUS_DpAlarm(this);
    mAlarmSlave = new BUS_DpAlarmSave(this);

    mEnv = new BUS_DpSaveEnv(this);
    mThreshold = new BUS_DpSaveThreshold(this);
    mRecord = new BUS_DpSaveRecord(this);
    mTrans = new BUS_DpSaveTrans(this);

    timer = new QTimer(this);
    timer->start(60*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

BUS_DpThread::~BUS_DpThread()
{
    isRun = false;
    wait();
}

BUS_DpThread *BUS_DpThread::bulid(QObject *parent)
{
    static BUS_DpThread* sington = NULL;
    if(sington == NULL) {
        sington = new BUS_DpThread(parent);
    }
    return sington;
}


void BUS_DpThread::saveModbusCmd(QStringList &list)
{
    BusDbModbusCmdItem item;
    item.bus = list.at(0);
    item.box = list.at(1);
    item.msg = list.at(2);

    QWriteLocker locker(mRwLock); // 正在操作时不允许关闭
    BusDbModbusCmd::bulid()->insertItem(item);
    msleep(30);
}

void BUS_DpThread::workDone()
{
    mTg->tg();
    mAlarm->alarm();
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

void BUS_DpThread::run()
{
    if(isRun == false)
    {
        isRun  = true;

        QWriteLocker locker(mRwLock); // 正在操作时不允许关闭
        workDone();
        isRun  = false;
    }
}

void BUS_DpThread::timeoutDone()
{
     sConfigItem *item = BUS_ConfigFile::bulid()->item;
    int num = item->logMins;
    if(mCount++ % num == 0) {
        if(item->testMode == BUS_Test_Simulate)
            isSave = true;
        else
            mCount = 1;
    }

}
