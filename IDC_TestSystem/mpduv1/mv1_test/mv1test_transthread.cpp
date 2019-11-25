#include "mv1test_transthread.h"
#include "mv1_rtu/mv1_rtuthread.h"
#include "mv1_snmp/mv1_snmptrans.h"

MV1Test_TransThread::MV1Test_TransThread(QObject *parent) : TestTransThread(parent)
{

}


void MV1Test_TransThread::initFunSLot()
{
    mRtu = MV1_RtuThread::bulid();
    mSnmp = MV1_SnmpTrans::bulid();
    mRtuTrans = MV1_RtuTrans::bulid();
}
