#ifndef IP_SIMULATEWID_H
#define IP_SIMULATEWID_H

#include "ip_transtablewid.h"
#include "ip_simulatethread.h"

namespace Ui {
class IP_SimulateWid;
}

class IP_SimulateWid : public QWidget
{
    Q_OBJECT

public:
    explicit IP_SimulateWid(QWidget *parent = 0);
    ~IP_SimulateWid();

signals:
     void updateSig();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();
     void timeoutDone();

private:
    Ui::IP_SimulateWid *ui;

    QTimer *timer;
    IP_DevTableWid *mDevTableWid;
    IP_EnvTableWid *mEnvTableWid;
    IP_ThresholdTableWid *mThresholdTableWid;
    IP_TransTableWid *mTransTableWid;
    IP_SimulateThread *mSimulateThread;
};

#endif // IP_SIMULATEWID_H
