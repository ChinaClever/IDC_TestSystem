#ifndef MPDU_MAINWID_H
#define MPDU_MAINWID_H

#include "mpdu_toolbox/mpdu_toolboxwid.h"
#include "mpdu_rtu_test/mpdurtutest_mainwid.h"
#include "m_logs/m_logswid.h"
#include "m_simulate/m_simulatewid.h"

namespace Ui {
class MPDU_MainWid;
}

class MPDU_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit MPDU_MainWid(QWidget *parent = 0);
    ~MPDU_MainWid();

protected slots:
    void initFunSLot();
    void toolBoxSlot(int);

private:
    Ui::MPDU_MainWid *ui;
    MPDU_ToolBoxWid *mtoolBoxWid;
    MpduRtuTest_MainWid *mTestWid;

    M_SimulateWid *mSimulateWid;
    M_LogsWid *mLogsWid;
};

#endif // MPDU_MAINWID_H
