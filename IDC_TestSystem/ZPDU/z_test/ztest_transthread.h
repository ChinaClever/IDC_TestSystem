#ifndef ZTEST_TRANSTHREAD_H
#define ZTEST_TRANSTHREAD_H
#include "testcorethread.h"

class ZTest_TransThread : public TestTransThread
{
    Q_OBJECT
    explicit ZTest_TransThread(QObject *parent = nullptr);
public:
    static ZTest_TransThread *bulid(QObject *parent = nullptr);

signals:

public slots:
     void initFunSLot();
};

#endif // ZTEST_TRANSTHREAD_H
