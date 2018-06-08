#ifndef BUS_TOOLBOXWID_H
#define BUS_TOOLBOXWID_H

#include "bus_simulationtoolwid.h"

namespace Ui {
class BUS_ToolBoxWid;
}

class BUS_ToolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_ToolBoxWid(QWidget *parent = 0);
    ~BUS_ToolBoxWid();

signals:
     void toolBoxSig(int);

protected:
    void initWid();

private:
    Ui::BUS_ToolBoxWid *ui;

    BUS_SettingToolWid *mSettingToolWid;
    BUS_SimulationToolWid *mSimulationToolWid;
};

#endif // BUS_TOOLBOXWID_H
