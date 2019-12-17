/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_dpthread.h"

MV1_DpThread::MV1_DpThread(QObject *parent) : DpThread(parent)
{
    mEnv = new MV1_DpSaveEnv(this);
    mOutput = new MV1_DpSaveOutput(this);
    mLine = new MV1_DpSaveLineRecord(this);
    mTrans = new MV1_DpSaveTrans(this);
    mAlarmSlave = new MV1_DpAlarmSave(this);
    mLineThreshold = new MV1_DpSaveLineThreshold(this);

    sDevPackets *packets = MV1_DataPackets::bulid()->packets;
    initPackets(packets);
}

MV1_DpThread::~MV1_DpThread()
{
    isRun = false;
    wait();
}


MV1_DpThread *MV1_DpThread::bulid(QObject *parent)
{
    static MV1_DpThread* sington = NULL;
    if(sington == NULL) {
        sington = new MV1_DpThread(parent);
    }
    return sington;
}

bool MV1_DpThread::getStart()
{
    bool ret = false;
    if(MV1_ConfigFile::bulid()->item->testMode == Test_SNMP)
        ret = true;
    return ret;
}
