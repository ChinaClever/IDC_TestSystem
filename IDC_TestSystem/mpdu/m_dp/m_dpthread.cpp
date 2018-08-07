/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_dpthread.h"

M_DpThread::M_DpThread(QObject *parent) : DpThread(parent)
{
    mEnv = new M_DpSlaveEnv(this);
    mOutput = new M_DpSaveOutput(this);
    mLine = new M_DpSlaveLineRecord(this);
    mTrans = new M_DpSlaveTrans(this);
    mAlarmSlave = new M_DpAlarmSlave(this);
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
