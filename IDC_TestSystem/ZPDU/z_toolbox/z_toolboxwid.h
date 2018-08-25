#ifndef Z_TOOLBOXWID_H
#define Z_TOOLBOXWID_H

#include "z_logstoolwid.h"

namespace Ui {
class Z_ToolBoxWid;
}

class Z_ToolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit Z_ToolBoxWid(QWidget *parent = 0);
    ~Z_ToolBoxWid();

signals:
     void toolBoxSig(int);

protected:
    void initWid();

private:
    Ui::Z_ToolBoxWid *ui;

    Z_SettingToolWid *mSettingToolWid;
    Z_LogsToolWid *mLogsToolWid;
    Z_SimulationToolWid *mSimulationToolWid;
};

#endif // Z_TOOLBOXWID_H
