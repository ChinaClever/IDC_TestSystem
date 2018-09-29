#ifndef TESTCORETHREAD_H
#define TESTCORETHREAD_H

#include "testtransthread.h"
#include "testdatasave.h"

class TestCoreThread : public QThread
{
    Q_OBJECT
public:
    explicit TestCoreThread(QObject *parent = nullptr);

    void init(sTestConfigItem *item){ mItem = item; }
    void startThread();

private:
    void stopThread();

    void conditionExec(bool s);
    bool appendResult(sTestDataItem &item);
    bool snmpTrans();
    bool rtuTrans();
    bool transmission();



signals:

public slots:

protected:
    int mItemId;
    TestTransThread *mTrans;
    sDevPackets *mPackets;

private:
    sTestConfigItem  *mItem;
    sDataPacket *mDevPacket;
};

#endif // TESTCORETHREAD_H
