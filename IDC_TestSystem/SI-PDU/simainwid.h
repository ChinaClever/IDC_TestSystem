#ifndef SIMAINWID_H
#define SIMAINWID_H

#include <QWidget>
#include "toolbox/sitoolboxwid.h"
#include "si_simulate/si_simulatethread.h"
#include "si_logs/silogalarmwid.h"
#include "si_simulate/si_devtablewid.h"
#include "si_setting/si_setmainwid.h"
#include "si_service/si_servicethread.h"

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
    void initFunSLot();
    void toolBoxSlot(int);

private:
    Ui::SIMainWid *ui;

    SitoolBoxWid *mtoolBoxWid;
    SI_SimulateThread *mSimulateThread;

    SI_DevTableWid *mDevTableWid;
    SI_EnvTableWid *mEnvTableWid;
    SI_SetMainWid *mSetMainWid;
    SI_TransTableWid *mTransTableWid;
    SI_ThresholdTableWid *mThresholdTableWid;

    SiLogEnvWid *mLogEnvWid;
    SiLogAlarmWid *mLogAlarmWid;
    SiLogModbusCmdWid *mLogModbusCmdWid;
    SiLogModbusTransWid *mLogModbusTransWid;
    SiLogRealRecordWid *mLogRealRecordWid;
    SiLogThresholdWid *mLogThresholdWid;
    SI_ServiceThread *mServiceThread;
};

#endif // SIMAINWID_H
