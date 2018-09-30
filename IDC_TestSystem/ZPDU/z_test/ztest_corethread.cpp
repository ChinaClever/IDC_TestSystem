#include "ztest_corethread.h"

ZTest_CoreThread::ZTest_CoreThread(QObject *parent) : TestCoreThread(parent)
{
    mTrans = ZTest_TransThread::bulid();
}
