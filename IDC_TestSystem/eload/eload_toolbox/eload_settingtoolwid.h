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
    void on_devNumBtn_clicked();
    void on_cmdBtn_clicked();
    void on_timeBtn_clicked();

private:
    Ui::ELoad_SettingToolWid *ui;
    SerialPortDlg *mSerialPortDlg;
};

#endif // ELOAD_SETTINGTOOLWID_H
