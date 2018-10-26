#include "testtransthread.h"

TestTransThread::TestTransThread(QObject *parent) : QThread(parent)
{
    mRtu = nullptr;
    mSnmp = nullptr;
    mRtuTrans = nullptr;
    mRtuLock = false;

    mStep = 0;
    timer = new QTimer(this);
    timer->start(500);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    QTimer::singleShot(1400,this,SLOT(initFunSLot()));
}

TestTransThread::~TestTransThread()
{
    wait();
}

void TestTransThread::timeoutDone()
{
    switch (mStep) {
    case 1: rtuUpdate(); break;
    case 2: snmpUpdate(); break;
    case 3: rtuStopData(); break;
    case 4: snmpStopData(); break;
    case 5: stopUpdate(); break;
    case 6: start(); break;
    default:  break;
    }
    mStep = 0;
}

void TestTransThread::snmpUpdate(int s)
{
    mSnmp->startRun();
    if(s) QTimer::singleShot(s *1000,this,SLOT(snmpStopData()));
}

bool TestTransThread::rtuUpdate(int s)
{
    bool ret = true;
    if(!mRtuLock) {
        mRtuLock = true;
        mRtu->startThread();
        if(s) QTimer::singleShot(s *1000,this,SLOT(rtuStopData()));
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
        mStep = 6;
    }
    mRtuCmdList.append(cmd);
}

void TestTransThread::setRtuValue(QList<sRtuSetCmd> &cmd)
{
    for( const auto& value : cmd ) {
        setRtuValue(value);
    }
}

void TestTransThread::rtuStopData()
{
    mRtu->stopThread();
    mRtuLock = false;
}

void TestTransThread::clearSnmpCmd()
{
    mSnmp->mSetCmdList.clear();
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
