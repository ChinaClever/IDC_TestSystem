#ifndef RTEST_CORETHREAD_H
#define RTEST_CORETHREAD_H

#include "rtest_transthread.h"

class RTest_CoreThread : public TestCoreThread
{
    Q_OBJECT
public:
    explicit RTest_CoreThread(QObject *parent = nullptr);

    bool lineVolCmd(sTestSetCmd &it);
    bool loopVolCmd(sTestSetCmd &it);

    bool lineCurCmd(sTestSetCmd &it);
    bool loopCurCmd(sTestSetCmd &it);
    bool outputCurCmd(sTestSetCmd &it);

    bool outputSwCmd(sTestSetCmd &it);

    bool outputEleCmd(sTestSetCmd &it);
    bool lineEleCmd(sTestSetCmd &it);
    bool temHumCmd(sTestSetCmd &it);

    void temCmd(sTestSetCmd &it);
    void humCmd(sTestSetCmd &it);

    void outputCloseSwCmd(sTestSetCmd &it);
    void outputCloseAndOpenIndexSwCmd(sTestSetCmd &it,int index);

    bool clearEleCmd(sTestSetCmd &it);
    bool setFactoryCmd(sTestSetCmd &it);
};

#endif // RTEST_CORETHREAD_H
