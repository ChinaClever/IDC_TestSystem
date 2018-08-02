#ifndef IP_SIMULATETHREAD_H
#define IP_SIMULATETHREAD_H

#include "ip_com/ipdatapackets.h"
#include "ip_dp/ip_dpthread.h"

class IP_SimulateThread : public QThread
{
    Q_OBJECT
public:
    explicit IP_SimulateThread(QObject *parent = nullptr);
    ~IP_SimulateThread();

protected:
    void run();
    void workDown();
    void sentOkCmd(sRtuCount &count);
    void saveErrCmd(int id, sRtuCount &count);
    void setOffLine();
    void clearCount();

signals:

public slots:
    void startThread();
    void stopThread();

private slots:
    void initSlot();

private:
    bool isRun;

    sDevPackets *mPackets;
    IP_RtuTrans *mRtu;
    IP_DpThread *mDpThread;
};

#endif // IP_SIMULATETHREAD_H
