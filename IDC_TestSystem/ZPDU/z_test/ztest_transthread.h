#ifndef ZTEST_TRANSTHREAD_H
#define ZTEST_TRANSTHREAD_H

#include "testtransthread.h"

class ZTest_TransThread : public TestTransThread
{
    Q_OBJECT
public:
    explicit ZTest_TransThread(QObject *parent = nullptr);

signals:

public slots:
     void initFunSLot();
};

#endif // ZTEST_TRANSTHREAD_H
