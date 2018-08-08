#ifndef IP_MAINWID_H
#define IP_MAINWID_H

#include "ip_simulate/ip_simulatewid.h"
#include "ip_toolbox/ip_toolboxwid.h"
#include "ip_logs/iplogswid.h"
#include "ip_service/ip_servicethread.h"

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
};

#endif // IP_MAINWID_H
