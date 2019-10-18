#ifndef RTEST_CORETHREAD_H
#define RTEST_CORETHREAD_H

#include "rtest_transthread.h"

class RTest_CoreThread : public TestCoreThread
{
    Q_OBJECT
public:
    explicit RTest_CoreThread(QObject *parent = nullptr);


protected:
    virtual int snmpTransDelay() {return 15;}
    virtual int rtuTransDelay() {return 40;}
    virtual void lineCurAlarmDelay() {sleep(10);}
    virtual int outputCurAlarmDelay() {return 30;}
    virtual int outputSwCtrDelay();
    virtual bool getLinePow(int id, int &measure);
    virtual bool getOutputPow(int id, int &measure);
    virtual int getEnvs();
    virtual void temHumAlarm(){}
    virtual int getDoors();
    virtual int bigCurDelay() {return 21;}
    virtual void curCheckDelay();

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
    virtual bool curBigAccuracy(ushort index, ushort *measured, sTestDataItem &item);
};

#endif // RTEST_CORETHREAD_H
