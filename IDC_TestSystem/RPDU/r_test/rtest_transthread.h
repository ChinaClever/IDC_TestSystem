#ifndef RTEST_TRANSTHREAD_H
#define RTEST_TRANSTHREAD_H
#include "testcorethread.h"

class RTest_TransThread : public TestTransThread
{
    Q_OBJECT
public:
    explicit RTest_TransThread(QObject *parent = nullptr);

protected:
    virtual void delay() {sleep(3);}

public slots:
     void initFunSLot();
};

#endif // RTEST_TRANSTHREAD_H
