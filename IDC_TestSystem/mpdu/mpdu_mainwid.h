#ifndef MPDU_MAINWID_H
#define MPDU_MAINWID_H

#include "m_toolbox/mpdu_toolboxwid.h"
#include "m_test/mtest_mainwid.h"
#include "m_logs/m_logswid.h"
#include "m_simulate/m_simulatewid.h"
#include "m_service/m_servicethread.h"

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
    MTest_MainWid *mTestWid;

    M_SimulateWid *mSimulateWid;
    M_LogsWid *mLogsWid;
    M_ServiceThread *mServiceThread;
};

#endif // MPDU_MAINWID_H
