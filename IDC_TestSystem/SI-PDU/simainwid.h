#ifndef SIMAINWID_H
#define SIMAINWID_H

#include "si_toolbox/si_toolboxwid.h"
#include "si_logs/silogswid.h"
#include "si_setting/si_setmainwid.h"
#include "si_service/si_servicethread.h"
#include "si_rtu/si_rtuthread.h"
#include "si_status/si_statuswid.h"

namespace Ui {
class SIMainWid;
}

class SIMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit SIMainWid(QWidget *parent = 0);
    ~SIMainWid();


private slots:
    void initFunSLot();
    void timeoutDone();
    void toolBoxSlot(int);

private:
    Ui::SIMainWid *ui;

    SI_ToolBoxWid *mtoolBoxWid;
    SI_StatusWid *mStatusWid;
    SI_SetMainWid *mSetMainWid;
    SI_ServiceThread *mServiceThread;
    SILogsWid *mLogsWid;

    SI_DpThread *mDpThread;
    SI_RtuThread *mRtuThread;
    QTimer *timer;
};

#endif // SIMAINWID_H
