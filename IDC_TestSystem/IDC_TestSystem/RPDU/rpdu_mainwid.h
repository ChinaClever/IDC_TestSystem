#ifndef RPDU_MAINWID_H
#define RPDU_MAINWID_H

#include "r_toolbox/r_toolboxwid.h"
#include "r_logs/r_logswid.h"
#include "r_service/r_servicethread.h"
#include "r_setting/rset_mainwid.h"
#include "r_rtu/r_rtuthread.h"
#include "r_status/r_statuswid.h"
#include "r_status/r_statuswid.h"
#include "r_snmp/r_snmptrans.h"
#include "r_test/rtest_mainwid.h"

namespace Ui {
class RPDU_MainWid;
}

class RPDU_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit RPDU_MainWid(QWidget *parent = 0);
    ~RPDU_MainWid();

protected slots:
    void initFunSLot();
    void toolBoxSlot(int);
    void timeoutDone();

signals:
    void autoTestChange();

private:
    Ui::RPDU_MainWid *ui;

    R_ToolBoxWid *mtoolBoxWid;
    R_StatusWid *mStatusWid;
    R_LogsWid *mLogsWid;
    R_ServiceThread *mServiceThread;
    RSet_MainWid *mSetWid;
    RTest_MainWid *mTestWid;

    R_SnmpTrans *mSnmp;
    R_DpThread *mDpThread;
    R_RtuThread *mRtuThread;
    QTimer *timer;
};

#endif // RPDU_MAINWID_H
