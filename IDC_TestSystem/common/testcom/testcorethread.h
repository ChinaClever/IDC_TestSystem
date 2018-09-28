#ifndef TESTCORETHREAD_H
#define TESTCORETHREAD_H

#include "testtransthread.h"

class TestCoreThread : public QThread
{
    Q_OBJECT
public:
    explicit TestCoreThread(QObject *parent = nullptr);

signals:

public slots:

protected:
    TestTransThread *mTrans;
};

#endif // TESTCORETHREAD_H
