#ifndef TESTTRANSTHREAD_H
#define TESTTRANSTHREAD_H

#include "rtuthread.h"
#include "snmpthread.h"

class TestTransThread : public QThread
{
    Q_OBJECT
public:
    explicit TestTransThread(QObject *parent = nullptr);
    ~TestTransThread();

    void rtuUpdateData() {mStep=1;}
    void snmpUpdateData() {mStep=2;}
    void stopUpdateData() {mStep=5;}
    void rtuStop()  {mStep=3;}
    void snmpStop() {mStep=4;}

    void setRtuValue(const sRtuSetCmd &cmd);
    void setRtuValue(QList<sRtuSetCmd> &cmd);

    void setSnmpValue(const sSnmpSetCmd &cmd);
    void setSnmpValue(QList<sSnmpSetCmd> &cmd);

    void clearSnmpCmd();//把上一次的snmp命令清除

protected:
    virtual void delay() {msleep(750);}

protected slots:
    void run();
    void rtuStopData();
    bool rtuUpdate(int s=15);
    void snmpUpdate(int s=15);
    void stopUpdate() {rtuStopData(); snmpStopData();}
    void snmpStopData() {mSnmp->stopRun();}
    void timeoutDone();
    virtual void initFunSLot()=0;

protected:
    RtuThread *mRtu;
    RtuTrans *mRtuTrans;
    SnmpThread *mSnmp;

private:
    bool mRtuLock;
    QTimer *timer;

    int mStep;
    QList<sRtuSetCmd> mRtuCmdList;
};

#endif // TESTTRANSTHREAD_H
