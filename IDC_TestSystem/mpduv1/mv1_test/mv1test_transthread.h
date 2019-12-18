#ifndef MV1TEST_TRANSTHREAD_H
#define MV1TEST_TRANSTHREAD_H

#include "testcorethread.h"

class MV1Test_TransThread : public TestTransThread
{
    Q_OBJECT
public:
    explicit MV1Test_TransThread(QObject *parent = nullptr);

signals:
protected:
    int delay() {return (1800);}

public slots:
    void initFunSLot();
};

#endif // MV1TEST_TRANSTHREAD_H
