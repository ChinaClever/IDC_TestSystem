#ifndef MV1TEST_CORETHREAD_H
#define MV1TEST_CORETHREAD_H

#include "mv1test_transthread.h"

class MV1Test_CoreThread : public TestCoreThread
{
    Q_OBJECT
public:
    explicit MV1Test_CoreThread(QObject *parent = nullptr);

    bool lineVolCmd(sTestSetCmd &it);
    bool loopVolCmd(sTestSetCmd &it);

    bool lineCurCmd(sTestSetCmd &it);
    bool loopCurCmd(sTestSetCmd &it);
    bool outputCurCmd(sTestSetCmd &it);

    bool outputSwCmd(sTestSetCmd &it);
    int outputCurAlarmDelay() {return 40;}

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
    int getLoopNum();
    int getLoopPorts();
    bool curAcc(int expect, int measured, sTestDataItem &item, double f);
};

#endif // MV1TEST_CORETHREAD_H
