#ifndef BUS_DPTHREAD_H
#define BUS_DPTHREAD_H

#include "bus_dpslavetrans.h"

class BUS_DpThread : public QThread
{
    Q_OBJECT
public:
    explicit BUS_DpThread(QObject *parent = nullptr);
    ~BUS_DpThread();

    void saveModbusCmd(QStringList &list);

protected:
    void run();
    void workDone();

protected slots:
    void timeoutDone();

private:
    int mCount;
    bool isRun, isSave;
    QTimer *timer;
    QReadWriteLock *mRwLock;

    BUS_DpTg *mTg;
    BUS_DpAlarm *mAlarm;
    BUS_DpAlarmSlave *mAlarmSlave;

    BUS_DpSlaveEnv *mEnv;
    BUS_DpSaveThreshold *mThreshold;
    BUS_DpSlaveRecord *mRecord;
    BUS_DpSlaveTrans *mTrans;
};

#endif // BUS_DPTHREAD_H
