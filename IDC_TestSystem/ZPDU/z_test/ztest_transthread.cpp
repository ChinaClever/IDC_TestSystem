#include "ztest_transthread.h"
#include "z_rtu/z_rtuthread.h"
#include "z_snmp/z_snmptrans.h"

ZTest_TransThread::ZTest_TransThread(QObject *parent) : TestTransThread(parent)
{

}

ZTest_TransThread *ZTest_TransThread::bulid(QObject *parent)
{
    static ZTest_TransThread* sington = NULL;
    if(sington == NULL) {
        sington = new ZTest_TransThread(parent);
    }
    return sington;
}

void ZTest_TransThread::initFunSLot()
{
    mRtu = Z_RtuThread::bulid();
    mSnmp = Z_SnmpTrans::bulid();
    mRtuTrans = Z_RtuTrans::bulid();
}
