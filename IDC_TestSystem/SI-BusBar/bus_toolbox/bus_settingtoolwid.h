#ifndef BUS_SETTINGTOOLWID_H
#define BUS_SETTINGTOOLWID_H

#include "bus_com/bus_configfile.h"


namespace Ui {
class BUS_SettingToolWid;
}

class BUS_SettingToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_SettingToolWid(QWidget *parent = 0);
    ~BUS_SettingToolWid();

protected:
    bool initSerialPort();
    void updateSerialWid();

    void initModbusTime();
    void updateModbusTime(int num);

    void initDevCmd();
    void updateDevCmd(int num);

    void initDevNum();
    void updateDevNum(int num);

private slots:
    void on_serialBtn_clicked();

    void on_cmdBtn_clicked();

    void on_timeBtn_clicked();

    void on_devNumBtn_clicked();

private:
    Ui::BUS_SettingToolWid *ui;
    SerialPortDlg *mSerialPortDlg;
};

#endif // BUS_SETTINGTOOLWID_H
