#ifndef SI_TOOLBOXWID_H
#define SI_TOOLBOXWID_H

#include "si_statustoolwid.h"

namespace Ui {
class SI_ToolBoxWid;
}

class SI_ToolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit SI_ToolBoxWid(QWidget *parent = 0);
    ~SI_ToolBoxWid();

signals:
     void toolBoxSig(int);

protected:
    void initWid();

private:
    Ui::SI_ToolBoxWid *ui;

    SI_SettingToolWid *mSettingToolWid;
    SI_LogsToolWid *mLogsToolWid;
    SI_ModeToolWid *mModeToolWid;
    SI_StatusToolWid *mStatusToolWid;
};

#endif // SI_TOOLBOXWID_H
