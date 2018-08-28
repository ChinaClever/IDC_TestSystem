#ifndef Z_SIMULATEWID_H
#define Z_SIMULATEWID_H

#include "z_com/z_datapackets.h"
#include "tablewid/linethresholdtablewid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"
#include "tablewid/looptablewid.h"
#include "tablewid/loopthresholdtablewid.h"
#include "z_simulatethread.h"

namespace Ui {
class Z_SimulateWid;
}

class Z_SimulateWid : public QWidget
{
    Q_OBJECT

public:
    explicit Z_SimulateWid(QWidget *parent = 0);
    ~Z_SimulateWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::Z_SimulateWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;
    LoopTableWid *mLoopTableWid;
    LoopThresholdTableWid *mLoopThresholdTableWid;

    OutputTableWid *mOutputTableWid;
    OutputThresholdTableWid *mOutputThresholdTableWid;
    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
    Z_SimulateThread *mSimulateThread;
};

#endif // Z_SIMULATEWID_H
