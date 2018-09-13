#ifndef MPDU_MAINWID_H
#define MPDU_MAINWID_H

#include "m_toolbox/mpdu_toolboxwid.h"
#include "m_test/mtest_mainwid.h"
#include "m_logs/m_logswid.h"
#include "m_service/m_servicethread.h"
#include "m_rtu/m_rtuthread.h"
#include "m_status/m_statuswid.h"
#include "m_snmp/m_snmptrans.h"

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
    void timeoutDone();

private:
    Ui::MPDU_MainWid *ui;
    MPDU_ToolBoxWid *mtoolBoxWid;
    MTest_MainWid *mTestWid;

    M_StatusWid *mStatusWid;
    M_LogsWid *mLogsWid;
    M_ServiceThread *mServiceThread;

    M_SnmpTrans *mSnmp;
    M_DpThread *mDpThread;
    M_RtuThread *mRtuThread;
    QTimer *timer;
};

#endif // MPDU_MAINWID_H
