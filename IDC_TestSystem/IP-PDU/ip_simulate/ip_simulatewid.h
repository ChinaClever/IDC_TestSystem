#ifndef IP_SIMULATEWID_H
#define IP_SIMULATEWID_H

#include "ip_simulatethread.h"
#include "tablewid/linethresholdtablewid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"

namespace Ui {
class IP_SimulateWid;
}

class IP_SimulateWid : public QWidget
{
    Q_OBJECT

public:
    explicit IP_SimulateWid(QWidget *parent = 0);
    ~IP_SimulateWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::IP_SimulateWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;

    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
    IP_SimulateThread *mSimulateThread;
};

#endif // IP_SIMULATEWID_H
