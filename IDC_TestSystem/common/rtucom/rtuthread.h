#ifndef RTUTHREAD_H
#define RTUTHREAD_H

#include "dpcom/dpthread.h"

class RtuThread : public QThread
{
    Q_OBJECT
public:
    explicit RtuThread(QObject *parent = nullptr);
    ~RtuThread();

protected:
    void run();
    virtual void workDown()=0;
    void sentOkCmd(sRtuCount &count);
    void saveErrCmd(int id, sRtuCount &count);
    virtual void writeErrCmd(int id)=0;
    void setOffLine();
    void clearCount();

signals:

public slots:
    void startThread();
    void stopThread();

protected slots:
    virtual void initSlot()=0;

protected:
    bool isRun;

    DpThread *mDpThread;
    sDevPackets *mPackets;
};

#endif // RTUTHREAD_H
