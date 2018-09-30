#ifndef ZTEST_CORETHREAD_H
#define ZTEST_CORETHREAD_H

#include "ztest_transthread.h"

class ZTest_CoreThread : public TestCoreThread
{
    Q_OBJECT
public:
    explicit ZTest_CoreThread(QObject *parent = nullptr);

    bool lineVolCmd(sTestSetCmd &it);
    bool loopVolCmd(sTestSetCmd &it);
};

#endif // ZTEST_CORETHREAD_H