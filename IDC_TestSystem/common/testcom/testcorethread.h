#ifndef TESTCORETHREAD_H
#define TESTCORETHREAD_H

#include "testtransthread.h"
#include "testdatasave.h"

struct sTestSetCmd
{
    int devId;
    int num;

    /**
     * 电压报警阈值：   100  200     正常阈值：170   245
     * 相电流报警阈值   10  16     正常阈值：0     32
     * 输出位电流报警阈值   10  16  正常阈值：0     16
     */

    QList<sSnmpSetCmd> sMin;
    QList<sSnmpSetCmd> sMax;
    QList<sSnmpSetCmd> sAlarmMin; // 最小值设为1
    QList<sSnmpSetCmd> sAlarmMax; // 最大值设为2

    QList<sRtuSetCmd> rtuMin;
    QList<sRtuSetCmd> rtuMax;
    QList<sRtuSetCmd> rtuAlarmMin;
    QList<sRtuSetCmd> rtuAlarmMax;
};


class TestCoreThread : public QThread
{
    Q_OBJECT
public:
    explicit TestCoreThread(QObject *parent = nullptr);
    ~TestCoreThread();

    void init(sTestConfigItem *item){ mItem = item; }
    void startThread();

    virtual bool lineVolCmd(sTestSetCmd &it)=0;
    virtual bool loopVolCmd(sTestSetCmd &it)=0;

protected:
    void run();

private:
    void stopThread();
    void updateData();

    void conditionExec(bool s);
    bool appendResult(sTestDataItem &item);

    /********检查通讯***************/
    bool snmpTrans();
    bool rtuTrans();
    bool transmission();  // 通讯

    bool volAccuracy(int expect, int measured, sTestDataItem &item);
    void lineVol(); // 想电压
    void loopVol(); // 回路电压

    void setAlarmCmd(sTestSetCmd &cmd, bool alrm);
    void setLineVolCmd(bool alrm);
    void setLoopVolCmd(bool alrm);

    void lineVolAlarm();
    void loopVolAlarm();

    void volCheck();

    bool curAccuracy(int expect, int measured, sTestDataItem &item);
    void lineNoCur();
    void loopNoCur();
    void outputNoCur();

    void lineCur();
    void loopCur();
    void outputCur();

    void curCheck();

signals:

public slots:

protected:
    TestTransThread *mTrans;
    sDevPackets *mPackets;

private:
    int mItemId;
    sTestConfigItem  *mItem;
    sDataPacket *mDevPacket;
};

#endif // TESTCORETHREAD_H
