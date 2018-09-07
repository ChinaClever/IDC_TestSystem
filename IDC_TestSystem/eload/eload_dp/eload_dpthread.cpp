#include "eload_dpthread.h"
#include "eload_com/eload_configfile.h"

ELoad_DpThread::ELoad_DpThread(QObject *parent) : DpThread(parent)
{
    mEnv = new ELoad_DpSaveEnv(this);
    mLine = new ELoad_DpSaveLineRecord(this);
    mTrans = new ELoad_DpSaveTrans(this);
    mAlarmSlave = new ELoad_DpAlarmSave(this);
    mLineThreshold = new ELoad_DpSaveLineThreshold(this);

    sDevPackets *packets = IN_DataPackets::bulid()->packets;
    initPackets(packets);
}

ELoad_DpThread::~ELoad_DpThread()
{
    isRun = false;
    wait();
}

bool ELoad_DpThread::getStart()
{
    bool ret = false;
    if(ELoad_ConfigFile::bulid()->item->testMode == ELoad_Test_Simulate)
        ret = true;
    return ret;
}
