#ifndef ELOAD_SETTINGTOOLWID_H
#define ELOAD_SETTINGTOOLWID_H

#include "serialportdlg.h"

namespace Ui {
class ELoad_SettingToolWid;
}

class ELoad_SettingToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_SettingToolWid(QWidget *parent = 0);
    ~ELoad_SettingToolWid();

protected:
    void initModbusTime();
    void updateModbusTime(int num);

    void initDevCmd();
    void updateDevCmd(int num);

private slots:
    void on_cmdBtn_clicked();
    void on_timeBtn_clicked();

private:
    Ui::ELoad_SettingToolWid *ui;
};

#endif // ELOAD_SETTINGTOOLWID_H
