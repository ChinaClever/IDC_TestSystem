/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_dpthread.h"
#include "ip_sql/ipdbmodbuscmd.h"

IP_DpThread::IP_DpThread(QObject *parent) : DpThread(parent)
{
    mEnv = new IP_DpSaveEnv(this);
    mLine = new IP_DpSaveRecord(this);
    mTrans = new IP_DpSaveTrans(this);
    mAlarmSlave = new IP_DpAlarmSave(this);
    mLineThreshold = new IP_DpSaveThreshold(this);

    sDevPackets *packets = IpDataPackets::bulid()->packets;
    initPackets(packets);
}

IP_DpThread::~IP_DpThread()
{
    isRun = false;
    wait();
}

bool IP_DpThread::getStart()
{
    bool ret = false;
    if(IP_ConfigFile::bulid()->item->testMode == IP_Test_Simulate)
        ret = true;
    return ret;
}
