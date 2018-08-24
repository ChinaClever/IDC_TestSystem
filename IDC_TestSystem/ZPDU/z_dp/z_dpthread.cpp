#include "z_dpthread.h"

Z_DpThread::Z_DpThread(QObject *parent) : DpThread(parent)
{
    mEnv = new Z_DpSaveEnv(this);
    mOutput = new Z_DpSaveOutput(this);
    mLine = new Z_DpSaveLineRecord(this);
    mLoop = new Z_DpSaveLoop(this);
    mTrans = new Z_DpSaveTrans(this);
    mAlarmSlave = new Z_DpAlarmSave(this);
    mLineThreshold = new Z_DpSaveLineThreshold(this);

    sDevPackets *packets = Z_DataPackets::bulid()->packets;
    initPackets(packets);
}

Z_DpThread::~Z_DpThread()
{
    isRun = false;
    wait();
}

bool Z_DpThread::getStart()
{
    bool ret = false;
    if(Z_ConfigFile::bulid()->item->testMode == Z_Test_Simulate)
        ret = true;
    return ret;
}

