#ifndef ZTEST_CORETHREAD_H
#define ZTEST_CORETHREAD_H

#include "ztest_transthread.h"

class ZTest_CoreThread : public TestCoreThread
{
    Q_OBJECT
public:
    explicit ZTest_CoreThread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ZTEST_CORETHREAD_H
