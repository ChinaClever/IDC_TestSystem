#include "testtransthread.h"

TestTransThread::TestTransThread(QObject *parent) : QThread(parent)
{
    mRtu = nullptr;
    mSnmp = nullptr;
    mRtuTrans = nullptr;
    QTimer::singleShot(1400,this,SLOT(initFunSLot()));
}

void TestTransThread::snmpUpdateData(int s)
{
    mSnmp->startRun();
    if(s) QTimer::singleShot(s *1000,this,SLOT(snmpStop()));
}

void TestTransThread::rtuUpdateData(int s)
{
    mRtu->startThread();
    if(s) QTimer::singleShot(s *1000,this,SLOT(rtuStop()));
}

void TestTransThread::setSnmpValue(sSnmpSetCmd &cmd)
{
    mSnmp->setValue(cmd);
}

void TestTransThread::setRtuValue(sRtuSetCmd &cmd)
{
    mRtuTrans->setValue(cmd);
}
