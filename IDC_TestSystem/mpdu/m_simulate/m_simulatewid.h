#ifndef M_SIMULATEWID_H
#define M_SIMULATEWID_H

#include "m_com/m_datapackets.h"
#include "tablewid/linethresholdtablewid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"
#include "tablewid/outputthresholdtablewid.h"
#include "m_simulatethread.h"

namespace Ui {
class M_SimulateWid;
}

class M_SimulateWid : public QWidget
{
    Q_OBJECT

public:
    explicit M_SimulateWid(QWidget *parent = 0);
    ~M_SimulateWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::M_SimulateWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;
    OutputTableWid *mOutputTableWid;
    OutputThresholdTableWid *mOutputThresholdTableWid;
    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
    M_SimulateThread *mSimulateThread;
};

#endif // M_SIMULATEWID_H
