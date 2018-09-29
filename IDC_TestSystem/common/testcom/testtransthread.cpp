#include "testtransthread.h"

TestTransThread::TestTransThread(QObject *parent) : QThread(parent)
{
    mRtu = nullptr;
    mSnmp = nullptr;
    mRtuTrans = nullptr;
    mRtuLock = false;
    QTimer::singleShot(1400,this,SLOT(initFunSLot()));
}

TestTransThread::~TestTransThread()
{
    wait();
}

void TestTransThread::snmpUpdateData(int s)
{
    mSnmp->startRun();
    if(s) QTimer::singleShot(s *1000,this,SLOT(snmpStop()));
}

bool TestTransThread::rtuUpdateData(int s)
{
    bool ret = true;
    if(!mRtuLock) {
        mRtuLock = true;
        mRtu->startThread();
        if(s) QTimer::singleShot(s *1000,this,SLOT(rtuStop()));
    } else {
        ret = false;
    }

    return ret;
}

void TestTransThread::setSnmpValue(const sSnmpSetCmd &cmd)
{
    mSnmp->setValue(cmd);
}

void TestTransThread::setSnmpValue(QList<sSnmpSetCmd> &cmd)
{
    for( const auto& value : cmd ) {
        setSnmpValue(value);
    }
}

void TestTransThread::setRtuValue(const sRtuSetCmd &cmd)
{
    if(mRtuCmdList.isEmpty()) {
        if(mRtuLock)  mRtu->stopThread();
        QTimer::singleShot(1000,this,SLOT(start()));
    }
    mRtuCmdList.append(cmd);
}

void TestTransThread::setRtuValue(QList<sRtuSetCmd> &cmd)
{
    for( const auto& value : cmd ) {
        setRtuValue(value);
    }
}

void TestTransThread::rtuStop()
{
    mRtu->stopThread();
    mRtuLock = false;
}

void TestTransThread::run()
{
    while(mRtuCmdList.size()) {
        mRtuTrans->setValue(mRtuCmdList.first());
        sleep(1);
        mRtuCmdList.removeFirst();
    }

    if(mRtuLock)   mRtu->startThread();
}
