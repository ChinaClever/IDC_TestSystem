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

    bool lineCurCmd(sTestSetCmd &it);
    int lineVolAlarmDelay() {return 15;}
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
    int outputCurAlarmDelay() {return 30;}
    int bigCurDelay() {return 25;}
    void curCheckDelay() {sleep(60);}
    void getSwDelay(){sleep(15);}
    int getCheckPow(){return 55;}
    int getCheckActivePow(){return 3;}
    int getDoors(){return 1;}
    bool getLinePow(int id, int &measure);
    bool getLoopPow(int id, int &measure);
};

#endif // ZTEST_CORETHREAD_H
