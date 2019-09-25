/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_dpthread.h"

R_DpThread::R_DpThread(QObject *parent) : DpThread(parent)
{
    mEnv = new R_DpSaveEnv(this);
    mOutput = new R_DpSaveOutput(this);
    mLine = new R_DpSaveLineRecord(this);
    mLoop = new R_DpSaveLoop(this);
    mTrans = new R_DpSaveTrans(this);
    mAlarmSlave = new R_DpAlarmSave(this);
    mLineThreshold = new R_DpSaveLineThreshold(this);

    sDevPackets *packets = R_DataPackets::bulid()->packets;
    initPackets(packets);
}

R_DpThread::~R_DpThread()
{
    isRun = false;
    wait();
}

R_DpThread *R_DpThread::bulid(QObject *parent)
{
    static R_DpThread* sington = NULL;
    if(sington == NULL) {
        sington = new R_DpThread(parent);
    }
    return sington;
}


bool R_DpThread::getStart()
{
    bool ret = false;
    if(R_ConfigFile::bulid()->item->testMode != Test_Stop)
        ret = true;
    return ret;
}

