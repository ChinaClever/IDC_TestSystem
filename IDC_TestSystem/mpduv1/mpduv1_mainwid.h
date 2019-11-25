#ifndef MPDUV1_MAINWID_H
#define MPDUV1_MAINWID_H

#include "mv1_toolbox/mpduv1_toolboxwid.h"
#include "mv1_setting/mv1set_mainwid.h"
#include "mv1_logs/mv1_logswid.h"
#include "mv1_service/mv1_servicethread.h"
#include "mv1_rtu/mv1_rtuthread.h"
#include "mv1_status/mv1_statuswid.h"
#include "mv1_snmp/mv1_snmptrans.h"
#include "mv1_test/mv1test_mainwid.h"

namespace Ui {
class MPDUV1_MainWid;
}

class MPDUV1_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit MPDUV1_MainWid(QWidget *parent = 0);
    ~MPDUV1_MainWid();

protected slots:
    void initFunSLot();
    void toolBoxSlot(int);
    void timeoutDone();

signals:
    void autoTestChange();

private:
    Ui::MPDUV1_MainWid *ui;
    MPDUV1_ToolBoxWid *mtoolBoxWid;
    MV1Set_MainWid *mSetWid;

    MV1_StatusWid *mStatusWid;
    MV1_LogsWid *mLogsWid;
    MV1_ServiceThread *mServiceThread;
    MV1Test_MainWid *mTestWid;

    MV1_SnmpTrans *mSnmp;
    MV1_DpThread *mDpThread;
    MV1_RtuThread *mRtuThread;
    QTimer *timer;
};

#endif // MPDUV1_MAINWID_H
