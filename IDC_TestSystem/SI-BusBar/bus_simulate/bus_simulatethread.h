#ifndef BUS_SIMULATETHREAD_H
#define BUS_SIMULATETHREAD_H

#include "bus_rtu/bus_rtutrans.h"
#include "bus_dp/bus_dpthread.h"

class BUS_SimulateThread : public QThread
{
    Q_OBJECT
public:
    explicit BUS_SimulateThread(QObject *parent = nullptr);
    ~BUS_SimulateThread();

protected:
    void run();
    void workDown();
    void sentOkCmd(sRtuCount &count);
    void saveErrCmd(int busId, sDataPacket *box);
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

    BusPacketSi *mPacket;
    BUS_RtuTrans *mRtu;
    BUS_DpThread *mDpThread;
};

#endif // BUS_SIMULATETHREAD_H
