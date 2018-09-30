#ifndef TOOLBOXWID_H
#define TOOLBOXWID_H

#include "testtoolwid.h"

namespace Ui {
class ToolBoxWid;
}

class ToolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBoxWid(QWidget *parent = 0);
    ~ToolBoxWid();

signals:
     void toolBoxSig(int);

protected slots:
    virtual void initFunSLot();

protected:
    Ui::ToolBoxWid *ui;

    ConfigBase *mConfig;
    SettingToolWid *mSettingToolWid;
    StatusToolWid *mStatusToolWid;
    LogsToolWid *mLogsToolWid;
    ModeToolWid *mModeToolWid;
    TestToolWid *mTestToolWid;
};

#endif // TOOLBOXWID_H
