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

    bool temHumCmd(sTestSetCmd &it);

    void temCmd(sTestSetCmd &it);
    void humCmd(sTestSetCmd &it);
    void outputCloseSwCmd(sTestSetCmd &it);
    void outputCloseAndOpenIndexSwCmd(sTestSetCmd &it,int index);

    bool clearEleCmd(sTestSetCmd &it);
    bool setFactoryCmd(sTestSetCmd &it);

    int rtuTransDelay() {return 70;}
    int getDoors(){return 0;}
    int firstOpDelay(){return (50);}
};

#endif // MTEST_CORETHREAD_H
