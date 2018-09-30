#include "ztest_corethread.h"

ZTest_CoreThread::ZTest_CoreThread(QObject *parent) : TestCoreThread(parent)
{
    mTrans = new ZTest_TransThread(this);
}

bool ZTest_CoreThread::lineVolCmd(sTestSetCmd &it)
{

}

bool ZTest_CoreThread::loopVolCmd(sTestSetCmd &it)
{

}
