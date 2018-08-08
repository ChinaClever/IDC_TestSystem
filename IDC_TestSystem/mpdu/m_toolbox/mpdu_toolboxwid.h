#ifndef MPDU_TOOLBOXWID_H
#define MPDU_TOOLBOXWID_H

#include "m_simulationtoolwid.h"

namespace Ui {
class MPDU_ToolBoxWid;
}

class MPDU_ToolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit MPDU_ToolBoxWid(QWidget *parent = 0);
    ~MPDU_ToolBoxWid();

signals:
     void toolBoxSig(int);

protected:
    void initWid();

private:
    Ui::MPDU_ToolBoxWid *ui;

    M_SettingToolWid *mSettingToolWid;
    M_LogsToolWid *mLogsToolWid;
    M_SimulationToolWid *mSimulationToolWid;
};

#endif // MPDU_TOOLBOXWID_H
