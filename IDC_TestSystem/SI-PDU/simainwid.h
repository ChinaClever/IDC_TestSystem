#ifndef SIMAINWID_H
#define SIMAINWID_H

#include <QWidget>
#include "toolbox/sitoolboxwid.h"
#include "si_simulate/si_simulatethread.h"
#include "si_logs/silogenvwid.h"
#include "si_simulate/si_devtablewid.h"
#include "si_logsthread/si_envlogthread.h"

namespace Ui {
class SIMainWid;
}

class SIMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit SIMainWid(QWidget *parent = 0);
    ~SIMainWid();

protected:
    void initWid();

private slots:
    void toolBoxSlot(int);

private:
    Ui::SIMainWid *ui;

    SitoolBoxWid *mtoolBoxWid;
    SI_SimulateThread *mSimulateThread;

    SI_DevTableWid *mDevTableWid;
    SI_EnvTableWid *mEnvTableWid;
    SI_TransTableWid *mTransTableWid;
    SI_ThresholdTableWid *mThresholdTableWid;

    SiLogEnvWid *mLogEnvWid;
    SiLogModbusCmdWid *mLogModbusCmdWid;
    SiLogModbusTransWid *mLogModbusTransWid;

    QList<SI_ComLogThread *> mLogThreads;

};

#endif // SIMAINWID_H
