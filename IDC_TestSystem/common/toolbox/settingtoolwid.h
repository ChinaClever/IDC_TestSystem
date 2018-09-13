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

protected:
    void initModbusTime();
    void updateModbusTime(int num);

    void initDevCmd();
    void updateDevCmd(int num);

    void initDevNum();
    void updateDevNum(int num);

    void initOutputNum();
    void updateOutputNum(int num);

    void initLineNum();
    void updateLineNum(int num);

protected slots:
    void initFunSLot();
    void on_devNumBtn_clicked();
    void on_outputNumBtn_clicked();
    void on_cmdBtn_clicked();
    void on_timeBtn_clicked();
    void on_lineBtn_clicked();

protected:
    Ui::SettingToolWid *ui;    
    ConfigBase *config;
};

#endif // SETTINGTOOLWID_H
