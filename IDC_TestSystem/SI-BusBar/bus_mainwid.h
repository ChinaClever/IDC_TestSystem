#ifndef BUS_MAINWID_H
#define BUS_MAINWID_H

#include <QWidget>
#include "bus_simulate/bus_boxtablewid.h"
#include "bus_simulate/bus_bustablewid.h"
#include "bus_simulate/bus_envtablewid.h"
#include "bus_toolbox/bus_toolboxwid.h"

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

private:
    Ui::BUS_MainWid *ui;

    BUS_ToolBoxWid *mtoolBoxWid;
    BUS_BusTableWid *mBusTableWid;
    BUS_BoxTableWid *mBoxTableWid;
    BUS_LoopTableWid *mLoopTableWid;
    BUS_TransTableWid *mTransTableWid;
    BUS_ThresholdTableWid *mThresholdTableWid;
    BUS_EnvTableWid *mEnvTableWid;
};

#endif // BUS_MAINWID_H
