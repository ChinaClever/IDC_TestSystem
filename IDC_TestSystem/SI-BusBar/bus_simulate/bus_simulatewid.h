#ifndef BUS_SIMULATEWID_H
#define BUS_SIMULATEWID_H

#include "bus_com/bus_configfile.h"
#include "bus_boxtablewid.h"
#include "bus_bustablewid.h"
#include "bus_envtablewid.h"
#include "bus_simulatethread.h"

namespace Ui {
class BUS_SimulateWid;
}

class BUS_SimulateWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_SimulateWid(QWidget *parent = 0);
    ~BUS_SimulateWid();

signals:
     void updateSig();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();
     void timeoutDone();

private:
    Ui::BUS_SimulateWid *ui;

    QTimer *timer;
    BUS_SimulateThread *mSimulateThread;
    BUS_BusTableWid *mBusTableWid;
    BUS_BoxTableWid *mBoxTableWid;
    BUS_LoopTableWid *mLoopTableWid;
    BUS_TransTableWid *mTransTableWid;
    BUS_ThresholdTableWid *mThresholdTableWid;
    BUS_EnvTableWid *mEnvTableWid;
};

#endif // BUS_SIMULATEWID_H
