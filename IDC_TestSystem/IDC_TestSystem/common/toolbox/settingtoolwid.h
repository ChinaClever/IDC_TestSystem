#ifndef SETTINGTOOLWID_H
#define SETTINGTOOLWID_H

#include "statustoolwid.h"

namespace Ui {
class SettingToolWid;
}

class SettingToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit SettingToolWid(QWidget *parent = 0);
    ~SettingToolWid();

    void init(ConfigBase *config) {mConfig= config;}
    void ippdu(bool hide = true);

protected:
    void initModbusTime();
    void updateModbusTime(int num);

    void initDevCmd();
    void updateDevCmd(int num);   

    void initOutputNum();
    void updateOutputNum(int num);

    void initLineNum();
    void updateLineNum(int num);

    void updateVersion(int num);
    void initVersion();

protected slots:
    void initFunSLot();
    void on_outputNumBtn_clicked();
    void on_cmdBtn_clicked();
    void on_timeBtn_clicked();
    void on_lineBtn_clicked();
    void on_vBtn_clicked();

protected:
    Ui::SettingToolWid *ui;    
    ConfigBase *mConfig;
};

#endif // SETTINGTOOLWID_H
