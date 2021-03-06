﻿#ifndef ZPDU_MAINWID_H
#define ZPDU_MAINWID_H

#include "z_toolbox/z_toolboxwid.h"
#include "z_logs/z_logswid.h"
#include "z_service/z_servicethread.h"
#include "z_setting/zset_mainwid.h"
#include "z_rtu/z_rtuthread.h"
#include "z_status/z_statuswid.h"
#include "z_status/z_statuswid.h"
#include "z_snmp/z_snmptrans.h"
#include "z_test/ztest_mainwid.h"

namespace Ui {
class ZPDU_MainWid;
}

class ZPDU_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZPDU_MainWid(QWidget *parent = 0);
    ~ZPDU_MainWid();

protected slots:
    void initFunSLot();
    void toolBoxSlot(int);
    void timeoutDone();

signals:
    void autoTestChange();

private:
    Ui::ZPDU_MainWid *ui;

    Z_ToolBoxWid *mtoolBoxWid;
    Z_StatusWid *mStatusWid;
    Z_LogsWid *mLogsWid;
    Z_ServiceThread *mServiceThread;
    ZSet_MainWid *mSetWid;
    ZTest_MainWid *mTestWid;

    Z_SnmpTrans *mSnmp;
    Z_DpThread *mDpThread;
    Z_RtuThread *mRtuThread;
    QTimer *timer;
};

#endif // ZPDU_MAINWID_H
