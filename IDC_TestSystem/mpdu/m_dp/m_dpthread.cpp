/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_dpthread.h"

M_DpThread::M_DpThread(QObject *parent) : DpThread(parent)
{
    mEnv = new M_DpSaveEnv(this);
    mOutput = new M_DpSaveOutput(this);
    mLine = new M_DpSaveLineRecord(this);
    mTrans = new M_DpSaveTrans(this);
    mAlarmSlave = new M_DpAlarmSave(this);
    mLineThreshold = new M_DpSaveLineThreshold(this);

    sDevPackets *packets = M_DataPackets::bulid()->packets;
    initPackets(packets);
}


bool M_DpThread::getStart()
{
    bool ret = false;
    if(M_ConfigFile::bulid()->item->testMode == M_Test_Simulate)
        ret = true;
    return ret;
}
