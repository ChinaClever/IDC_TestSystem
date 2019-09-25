#ifndef IP_RTUTHREAD_H
#define IP_RTUTHREAD_H

#include "ip_com/ipdatapackets.h"
#include "ip_dp/ip_dpthread.h"
#include "rtucom/rtuthread.h"
#include "ip_rtutrans.h"

class IP_RtuThread : public RtuThread
{
    Q_OBJECT
    explicit IP_RtuThread(QObject *parent = nullptr);
public:
    static IP_RtuThread *bulid(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    IP_RtuTrans *mRtu;
};

#endif // IP_RTUTHREAD_H
