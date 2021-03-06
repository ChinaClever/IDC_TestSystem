#ifndef BUS_MAINWID_H
#define BUS_MAINWID_H

#include <QWidget>
#include "bus_toolbox/bus_toolboxwid.h"
#include "bus_logs/buslogswid.h"
#include "bus_simulate/bus_simulatewid.h"

namespace Ui {
class BUS_MainWid;
}

class BUS_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_MainWid(QWidget *parent = 0);
    ~BUS_MainWid();

protected slots:
    void initFunSLot();
    void toolBoxSlot(int);

private:
    Ui::BUS_MainWid *ui;

    BUS_ToolBoxWid *mtoolBoxWid;
    BUS_SimulateWid *mSimulateWid;
    BusLogsWid *mLogsWid;
};

#endif // BUS_MAINWID_H
