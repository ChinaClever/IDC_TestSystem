/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "rtest_transthread.h"
#include "r_rtu/r_rtuthread.h"
#include "r_snmp/r_snmptrans.h"

RTest_TransThread::RTest_TransThread(QObject *parent) : TestTransThread(parent)
{

}

void RTest_TransThread::initFunSLot()
{
    mRtu = R_RtuThread::bulid();
    mSnmp = R_SnmpTrans::bulid();
    mRtuTrans = R_RtuTrans::bulid();
}
