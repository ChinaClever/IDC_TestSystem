#ifndef MTEST_CORETHREAD_H
#define MTEST_CORETHREAD_H

#include "mtest_transthread.h"

class MTest_CoreThread : public TestCoreThread
{
    Q_OBJECT
public:
    explicit MTest_CoreThread(QObject *parent = nullptr);

    bool lineVolCmd(sTestSetCmd &it);
    bool loopVolCmd(sTestSetCmd &it);

    bool lineCurCmd(sTestSetCmd &it);
    bool loopCurCmd(sTestSetCmd &it);
    bool outputCurCmd(sTestSetCmd &it);

    bool outputSwCmd(sTestSetCmd &it);

    bool outputEleCmd(sTestSetCmd &it);
    bool lineEleCmd(sTestSetCmd &it);
};

#endif // MTEST_CORETHREAD_H
