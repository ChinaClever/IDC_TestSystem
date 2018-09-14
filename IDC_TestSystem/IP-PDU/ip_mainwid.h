#ifndef IP_MAINWID_H
#define IP_MAINWID_H

#include "ip_toolbox/ip_toolboxwid.h"
#include "ip_logs/iplogswid.h"
#include "ip_service/ip_servicethread.h"
#include "ip_rtu/ip_rtuthread.h"
#include "ip_status/ip_statuswid.h"

namespace Ui {
class IP_MainWid;
}

class IP_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit IP_MainWid(QWidget *parent = 0);
    ~IP_MainWid();

protected slots:
    void initFunSLot();
    void toolBoxSlot(int);

private:
    Ui::IP_MainWid *ui;
    IP_SimulateWid *mSimulateWid;
    IP_ToolBoxWid *mtoolBoxWid;
    IpLogsWid *mLogsWid;
    IP_ServiceThread *mServiceThread;

//    IP_SnmpTrans *mSnmp;
    IP_DpThread *mDpThread;
    IP_RtuThread *mRtuThread;
    QTimer *timer;
};

#endif // IP_MAINWID_H
