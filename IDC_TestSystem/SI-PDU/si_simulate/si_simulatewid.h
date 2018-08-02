#ifndef SI_SIMULATEWID_H
#define SI_SIMULATEWID_H

#include "si_simulatethread.h"
#include "tablewid/linethresholdtablewid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"

namespace Ui {
class SI_SimulateWid;
}

class SI_SimulateWid : public QWidget
{
    Q_OBJECT

public:
    explicit SI_SimulateWid(QWidget *parent = 0);
    ~SI_SimulateWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::SI_SimulateWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;

    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
    SI_SimulateThread *mSimulateThread;
};

#endif // SI_SIMULATEWID_H
