#include "ztest_transthread.h"
#include "z_rtu/z_rtuthread.h"
#include "z_snmp/z_snmptrans.h"

ZTest_TransThread::ZTest_TransThread(QObject *parent) : TestTransThread(parent)
{

}

void ZTest_TransThread::initFunSLot()
{
    mRtu = Z_RtuThread::bulid();
    mSnmp = Z_SnmpTrans::bulid();
    mRtuTrans = Z_RtuTrans::bulid();
}
