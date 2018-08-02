#ifndef SI_DPTHREAD_H
#define SI_DPTHREAD_H

#include "si_dpsavetrans.h"

class SI_DpThread : public QThread
{
    Q_OBJECT
public:
    explicit SI_DpThread(QObject *parent = nullptr);
    ~SI_DpThread();

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

    SI_DpAlarmSave *mAlarmSlave;
    SI_DpSaveEnv *mEnv;
    SI_DpSaveThreshold *mThreshold;
    SI_DpSaveRecord *mRecord;
    SI_DpSaveTrans *mTrans;
};

#endif // SI_DPTHREAD_H
