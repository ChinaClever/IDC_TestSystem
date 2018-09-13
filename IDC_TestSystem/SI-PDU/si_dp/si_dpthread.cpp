/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_dpthread.h"

SI_DpThread::SI_DpThread(QObject *parent) : DpThread(parent)
{
    mEnv = new SI_DpSaveEnv(this);
    mLine = new SI_DpSaveRecord(this);
    mTrans = new SI_DpSaveTrans(this);
    mAlarmSlave = new SI_DpAlarmSave(this);
    mLineThreshold = new SI_DpSaveThreshold(this);

    sDevPackets *packets = SIDataPackets::bulid()->packets;
    initPackets(packets);
}

SI_DpThread::~SI_DpThread()
{
    isRun = false;
    wait();
}

bool SI_DpThread::getStart()
{
    bool ret = false;
    if(SiConfigFile::bulid()->item->testMode == Test_Rtu)
        ret = true;
    return ret;
}
