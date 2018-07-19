#ifndef IP_DPTHREAD_H
#define IP_DPTHREAD_H

#include "ip_dpalarmslave.h"

class IP_DpThread : public QThread
{
    Q_OBJECT
public:
    explicit IP_DpThread(QObject *parent = nullptr);
    ~IP_DpThread();

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

    IP_DpAlarmSlave *mAlarmSlave;
    IP_DpSlaveEnv *mEnv;
    IP_DpSaveThreshold *mThreshold;
    IP_DpSlaveRecord *mRecord;
    IP_DpSlaveTrans *mTrans;
};

#endif // IP_DPTHREAD_H
