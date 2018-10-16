#ifndef TESTCORETHREAD_H
#define TESTCORETHREAD_H

#include "testtransthread.h"
#include "testdatasave.h"

#define TEST_NORMAL_VOL_MIN 170
#define TEST_NORMOL_VOL_MAX 245

#define TEST_ABNORMAL_VOL_MIN 100
#define TEST_ABNORMOL_VOL_MAX 200

enum {
    Test_Normal_VolMin  = 170,
    Test_Normal_VolMax  = 245,

    Test_Abnormal_VolMin  = 100,
    Test_Abnormal_VolMax  = 200,

    Test_Normal_CurMin  = 0,
    Test_Normal_LineCurMax  = 32,
    Test_Normal_OutputCurMax  = 32,

    Test_Abnormal_CurMin  = 10,
    Test_Abnormal_CurMax  = 16,
};




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
    QList<sSnmpSetCmd> sAlarmMin; // 最小值设为
    QList<sSnmpSetCmd> sAlarmMax; // 最大值设为

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

    void init(sTestConfigItem *item, sDevPackets *packets, TestTransThread *trans);
    void startThread();

    virtual bool lineVolCmd(sTestSetCmd &it)=0;
    virtual bool loopVolCmd(sTestSetCmd &it)=0;

    virtual bool lineCurCmd(sTestSetCmd &it)=0;
    virtual bool loopCurCmd(sTestSetCmd &it)=0;
    virtual bool outputCurCmd(sTestSetCmd &it)=0;

    virtual bool outputSwCmd(sTestSetCmd &it)=0;
    virtual bool outputEleCmd(sTestSetCmd &it)=0;
    virtual bool lineEleCmd(sTestSetCmd &it)=0;


signals:
    void overSig();

protected:
    void run();

private:
    void stopThread();
    void updateData();
    void conditionExec(bool s);
    void updateProgress(bool status, QString &str);
    bool appendResult(sTestDataItem &item);
    void countItemsNum();

    /********检查通讯***************/
    bool snmpTrans();
    bool rtuTrans();
    bool transmission();  // 通讯

    bool volAccuracy(int expect, int measured, sTestDataItem &item);
    void lineVol(); // 相电压
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

    void setLineCurCmd(bool alrm);
    void setLoopCurCmd(bool alrm);
    void setOutputCurCmd(bool alrm);
    void lineCurAlarm();
    void loopCurAlarm();
    void outputCurAlarm();
    void curAlarmCheck();

    bool swAccuracy(int measured, sTestDataItem &item);
    void setOutputSwCmd(bool alrm);
    void outputSwCtr();
    void switchCtr();

    bool powAccuracy(int expect, int measured, sTestDataItem &item);
    void linePow();
    void loopPow();
    bool outputPow();
    void powCheck();

    bool eleAccuracy(int measured, sTestDataItem &item);
    void setOutputEleCmd();
    void setLineEleCmd();
    int outputEle();
    int lineEle();
    int loopEle();
    void eleCheck();

private:
    int mItemId;
    sTestConfigItem  *mItem;
    TestTransThread *mTrans;
    sDataPacket *mDevPacket;
    sDevPackets *mPackets;
};

#endif // TESTCORETHREAD_H
