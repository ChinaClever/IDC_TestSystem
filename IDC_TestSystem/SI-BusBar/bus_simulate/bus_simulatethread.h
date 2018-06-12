#ifndef BUS_SIMULATETHREAD_H
#define BUS_SIMULATETHREAD_H

#include "bus_simulatewid.h"
#include "bus_rtu/bus_rtutrans.h"

class BUS_SimulateThread : public QThread
{
    Q_OBJECT
public:
    explicit BUS_SimulateThread(QObject *parent = nullptr);
    ~BUS_SimulateThread();

protected:
    void run();
    void workDown();
    void sentOkCmd(BUS_RtuCount &count);
    void saveErrCmd(BUS_RtuCount &count);
    void setOffLine();

signals:

public slots:
    void startThread();
    void stopThread();

private slots:
    void initSlot();
    void timeoutDone();

private:
    bool isRun;

    QTimer *timer;
    BusPacketSi *mPacket;
    BUS_RtuTrans *mRtu;
};

#endif // BUS_SIMULATETHREAD_H
