#ifndef SIMAINWID_H
#define SIMAINWID_H

#include <QWidget>
#include "toolbox/sitoolboxwid.h"
#include "si_simulate/si_simulatethread.h"
#include "si_logs/silogswid.h"
#include "si_simulate/si_simulatewid.h"
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
    SI_SimulateWid *mSimulateWid;
    SI_SetMainWid *mSetMainWid;
    SI_ServiceThread *mServiceThread;
    SILogsWid *mLogsWid;
};

#endif // SIMAINWID_H
