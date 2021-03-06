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

    Test_Normal_TemMin  = 0,
    Test_Normal_TemMax  = 90,
    Test_Abnormal_TemMin  = 30,
    Test_Abnormal_TemMax  = 60,

    Test_Normal_HumMin  = 0,
    Test_Normal_HumMax  = 99,
    Test_Abnormal_HumMin  = 96,
    Test_Abnormal_HumMax  = 98,
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
    virtual bool temHumCmd(sTestSetCmd &it)=0;

    virtual void outputCloseSwCmd(sTestSetCmd &it)=0;
    virtual void outputCloseAndOpenIndexSwCmd(sTestSetCmd &it,int index)=0;

    virtual bool clearEleCmd(sTestSetCmd &it)=0;
    virtual bool setFactoryCmd(sTestSetCmd &it)=0;



signals:
    void overSig();

protected slots:
    void allNumsSlot(int nums);

protected:
    void run();
    void delay(int t) {if(isRun) sleep(t);}
    void mdelay(int t) {if(isRun) msleep(t);}

    virtual int snmpTransDelay() {return 10;}
    virtual int rtuTransDelay() {return 30;}
    virtual int lineCurAlarmDelay() {return (600);}
    virtual int lineVolAlarmDelay() {return 10;}
    virtual int outputCurAlarmDelay() {return 10;}
    virtual int outputSwCtrDelay() {return 30;}
    virtual int getLineNum();
    virtual int getLoopNum();
    virtual int getLinePorts();
    virtual int getLoopPorts();
    virtual bool getLinePow(int id , int &measure);
    virtual bool getLoopPow(int id, int &measure);
    virtual bool getOutputPow(int id, ushort &measure);
    virtual bool getBigOutputPow(int id, ushort **measure);
    virtual int getEnvs();
    virtual int bigCurDelay() {return 15;}

    virtual int curCheckDelay() {return (30);}
    virtual int firstOpDelay() {return (50);}
    virtual int getSwDelay(){return (5);}
    virtual int getCheckPow(){return 30;}
    virtual int getCheckActivePow(){return 1;}
    
    virtual bool curBigAccuracy(ushort index, ushort *premeasured, ushort *measured, sTestDataItem &item);

    virtual void lineVolAlarm();
    virtual bool devSpecCheck();
    virtual int getDoors() {return 2;}


    virtual void temHumAlarm();
    virtual bool curAcc(int expect, int measured, sTestDataItem &item, double f);
    bool curAcc(int expect,int premeasured, int measured, sTestDataItem &item, double f);

private:
    void stopThread();
    void updateData();
    void conditionExec(bool s);
    void updateProgress(bool status, QString &str);
    bool appendResult(sTestDataItem &item);

    /********检查通讯***************/
    bool snmpTrans();
    bool rtuTrans();
    bool transmission();  // 通讯

    bool devLineNumCheck();
    bool devLoopNumCheck();
    bool devOutputNumCheck();
    void devInfoCheck();

    bool volAccuracy(int expect, ushort &measured, sTestDataItem &item);
    void lineVol(); // 相电压
    void loopVol(); // 回路电压

    void setAlarmCmd(sTestSetCmd &cmd, bool alrm);
    void setLineVolCmd(bool alrm);
    void setLoopVolCmd(bool alrm);

    void loopVolAlarm();
    void volCheck();


    bool curAccuracy(int expect, int measured, sTestDataItem &item , double f=COM_RATE_CUR);//flag true cur/100 or false cur/10
    bool curNoCurAccuracy(int expect, int measured, sTestDataItem &item , double f=COM_RATE_CUR);
    bool curThresholdAccuracy(ushort expect, ushort &measured, sTestDataItem &item);
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

    bool swAccuracy(ushort &measured, sTestDataItem &item, uchar &sw, bool isOpen);
    void setOutputSwCmd(bool alrm);
    void outputSwCtr();
    void switchCtr();

    bool powAccuracy(int expect, int measured, sTestDataItem &item ,QString str);
    bool powBigAccuracy(int expect, ushort *measured, sTestDataItem &item, QString str);
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

    bool temAccuracy(int expect, int measured, sTestDataItem &item);
    bool humAccuracy(int expect, int measured, sTestDataItem &item);
    int getAvgValue(sDataUnit *unit, int num);
    void setTemHumAlarmCmd(bool alrm);
    void temCheck();
    void humCheck();
    void envCheck();
    void sensorsCheck();


    bool checkOutputZeroCur(int b, sTestDataItem &item ,bool flag=false);
    void bigCurCheck();
    void openOrCloseBigCur(bool mode);//mode:ture打开 false关闭
    void setBigCurCmd();
    void bigCurPowCheck(int i, int addr);

    void initSwitch();
    void resDev();
    double autoRate(int vol);
    void controlNoDelayBreaker(int id);

protected:
    int mItemId;
    sTestConfigItem  *mItem;
    TestTransThread *mTrans;
    sDataPacket *mDevPacket;
    sDevPackets *mPackets;
    double mRate;
    bool isRun;
};

#endif // TESTCORETHREAD_H
