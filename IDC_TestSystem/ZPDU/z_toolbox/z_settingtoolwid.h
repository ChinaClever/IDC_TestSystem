#ifndef Z_SETTINGTOOLWID_H
#define Z_SETTINGTOOLWID_H

#include "z_com/z_datapackets.h"

namespace Ui {
class Z_SettingToolWid;
}

class Z_SettingToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit Z_SettingToolWid(QWidget *parent = 0);
    ~Z_SettingToolWid();

protected:
    void initModbusTime();
    void updateModbusTime(int num);

    void initDevCmd();
    void updateDevCmd(int num);

    void initDevNum();
    void updateDevNum(int num);

private slots:
    void on_devNumBtn_clicked();
    void on_cmdBtn_clicked();
    void on_timeBtn_clicked();

private:
    Ui::Z_SettingToolWid *ui;
};

#endif // Z_SETTINGTOOLWID_H
