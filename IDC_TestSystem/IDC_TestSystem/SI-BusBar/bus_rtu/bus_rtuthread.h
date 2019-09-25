#ifndef BUS_RTUTHREAD_H
#define BUS_RTUTHREAD_H

#include "bus_com/buspacketsi.h"
#include "bus_dp/bus_dpthread.h"
#include "rtucom/rtuthread.h"
#include "bus_rtutrans.h"

class BUS_RtuThread : public RtuThread
{
    Q_OBJECT
    explicit BUS_RtuThread(QObject *parent = nullptr);
public:
    static BUS_RtuThread *bulid(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    int mBusId;
    BUS_RtuTrans *mRtu;
};

#endif // BUS_RTUTHREAD_H
