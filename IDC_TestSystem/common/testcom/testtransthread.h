#ifndef TESTTRANSTHREAD_H
#define TESTTRANSTHREAD_H

#include "rtuthread.h"
#include "snmpthread.h"

class TestTransThread : public QThread
{
    Q_OBJECT
public:
    explicit TestTransThread(QObject *parent = nullptr);

    void rtuUpdateData(int s=10);
    void snmpUpdateData(int s=5);

    void setRtuValue(sRtuSetCmd &cmd);
    void setSnmpValue(sSnmpSetCmd &cmd);

signals:

public slots:
    void snmpStop() {mSnmp->stopRun();}
    void rtuStop() {mRtu->stopThread();}
    virtual void initFunSLot()=0;

protected:
    RtuThread *mRtu;
    SnmpThread *mSnmp;
    RtuTrans *mRtuTrans;
};

#endif // TESTTRANSTHREAD_H
