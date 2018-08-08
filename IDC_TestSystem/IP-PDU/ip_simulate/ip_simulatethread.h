#ifndef IP_SIMULATETHREAD_H
#define IP_SIMULATETHREAD_H

#include "ip_com/ipdatapackets.h"
#include "ip_dp/ip_dpthread.h"
#include "tablewid/simulatethread.h"

class IP_SimulateThread : public SimulateThread
{
    Q_OBJECT
public:
    explicit IP_SimulateThread(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    IP_RtuTrans *mRtu;
};

#endif // IP_SIMULATETHREAD_H
