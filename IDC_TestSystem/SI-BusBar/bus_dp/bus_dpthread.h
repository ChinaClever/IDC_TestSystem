#ifndef BUS_DPTHREAD_H
#define BUS_DPTHREAD_H

#include "bus_dpsavetrans.h"

class BUS_DpThread : public QThread
{
    Q_OBJECT
    explicit BUS_DpThread(QObject *parent = nullptr);
public:
    static BUS_DpThread *bulid(QObject *parent);
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
    BUS_DpAlarmSave *mAlarmSlave;

    BUS_DpSaveEnv *mEnv;
    BUS_DpSaveThreshold *mThreshold;
    BUS_DpSaveRecord *mRecord;
    BUS_DpSaveTrans *mTrans;
};

#endif // BUS_DPTHREAD_H
