#ifndef ELOAD_TOOLBOXWID_H
#define ELOAD_TOOLBOXWID_H

#include "eload_inputtoolwid.h"
#include "eload_settingtoolwid.h"
#include "eload_logstoolwid.h"

namespace Ui {
class ELoad_ToolBoxWid;
}

class ELoad_ToolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_ToolBoxWid(QWidget *parent = 0);
    ~ELoad_ToolBoxWid();

signals:
     void toolBoxSig(int);
     void saveBoxSig();

protected:
    void initWid();

private:
    Ui::ELoad_ToolBoxWid *ui;

    ELoad_HomeToolWid *mHomeToolWid;
    ELoad_InputToolWid *mInputToolWid;
    ELoad_LogsToolWid *mLogsToolWid;
    ELoad_SettingToolWid *mSettingToolWid;
};

#endif // ELOAD_TOOLBOXWID_H
