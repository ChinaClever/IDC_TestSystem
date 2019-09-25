#ifndef MTEST_TRANSTHREAD_H
#define MTEST_TRANSTHREAD_H

#include "testcorethread.h"

class MTest_TransThread : public TestTransThread
{
    Q_OBJECT
public:
    explicit MTest_TransThread(QObject *parent = nullptr);

signals:

public slots:
    void initFunSLot();
};

#endif // MTEST_TRANSTHREAD_H
