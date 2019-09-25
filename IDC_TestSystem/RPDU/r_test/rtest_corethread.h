#ifndef RTEST_CORETHREAD_H
#define RTEST_CORETHREAD_H

#include "rtest_transthread.h"

class RTest_CoreThread : public TestCoreThread
{
    Q_OBJECT
public:
    explicit RTest_CoreThread(QObject *parent = nullptr);


protected:
    virtual void snmpTransDelay() {sleep(30);}
    virtual void rtuTransDelay() {sleep(30);}
    virtual void lineCurAlarmDelay() {sleep(50);}
    virtual void outputCurAlarmDelay() {sleep(100);}
    virtual void outputCurAlarmDelay2() {sleep(50);}
    virtual int getLineNum();
    virtual int getLoopNum();
    virtual void lineVolAlarm() {}
    virtual int getLinePorts();

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
