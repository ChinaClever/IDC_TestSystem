#ifndef IP_TOOLBOXWID_H
#define IP_TOOLBOXWID_H

#include "ip_statustoolwid.h"

namespace Ui {
class IP_ToolBoxWid;
}

class IP_ToolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit IP_ToolBoxWid(QWidget *parent = 0);
    ~IP_ToolBoxWid();

signals:
     void toolBoxSig(int);

protected:
    void initWid();

private:
    Ui::IP_ToolBoxWid *ui;

    IP_SettingToolWid *mSettingToolWid;
    IP_LogsToolWid *mLogsToolWid;
    IP_ModeToolWid *mModeToolWid;
    IP_StatusToolWid *mStatusToolWid;
};

#endif // IP_TOOLBOXWID_H
