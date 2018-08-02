#ifndef DPTHREAD_H
#define DPTHREAD_H

#include "dpsaveenv.h"
#include "dpsavetrans.h"
#include "dpsavelinethreshold.h"
#include "dpsaveline.h"

class DpThread : public QThread
{
    Q_OBJECT
public:
    explicit DpThread(QObject *parent = nullptr);
    ~DpThread();

    void initPackets(sDevPackets *packets);
    void saveModbusCmd(QStringList &list);

protected:
    void run();
    void workDone();
    virtual void insertItem(DbModbusCmdItem &item)=0;
    virtual int getTimeOut() = 0;
    virtual bool getStart() = 0;

protected slots:
    void timeoutDone();

protected:
    int mCount;
    bool isRun, isSave;
    QTimer *timer;
    QReadWriteLock *mRwLock;

    DpSaveEnv *mEnv;
    DpAlarmSave *mAlarmSlave;
    DpSaveLine *mLine;
    DpSaveLineThreshold *mLineThreshold;
    DpSaveTrans *mTrans;
};

#endif // DPTHREAD_H
