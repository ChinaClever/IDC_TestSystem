#include "mtest_transthread.h"
#include "m_rtu/m_rtuthread.h"
#include "m_snmp/m_snmptrans.h"

MTest_TransThread::MTest_TransThread(QObject *parent) : TestTransThread(parent)
{

}


void MTest_TransThread::initFunSLot()
{
    mRtu = M_RtuThread::bulid();
    mSnmp = M_SnmpTrans::bulid();
    mRtuTrans = M_RtuTrans::bulid();
}
