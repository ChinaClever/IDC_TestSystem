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

    bool rtuUpdateData(int s=10);
    void snmpUpdateData(int s=5);

    void setRtuValue(sRtuSetCmd &cmd);
    void setSnmpValue(sSnmpSetCmd &cmd);

protected:
    void run();

signals:

public slots:
    void rtuStop();
    virtual void initFunSLot()=0;
    void snmpStop() {mSnmp->stopRun();}

protected:
    RtuThread *mRtu;
    SnmpThread *mSnmp;
    RtuTrans *mRtuTrans;

private:
    bool mRtuLock;
    QList<sRtuSetCmd> mRtuCmdList;
};

#endif // TESTTRANSTHREAD_H
