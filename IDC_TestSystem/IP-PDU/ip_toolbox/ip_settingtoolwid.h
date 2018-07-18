#ifndef IP_SETTINGTOOLWID_H
#define IP_SETTINGTOOLWID_H

#include "ip_com/ipconfigfile.h"

namespace Ui {
class IP_SettingToolWid;
}

class IP_SettingToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit IP_SettingToolWid(QWidget *parent = 0);
    ~IP_SettingToolWid();


protected:
    bool initSerialPort();
    void updateSerialWid();

    void initModbusTime();
    void updateModbusTime(int num);

    void initDevCmd();
    void updateDevCmd(int num);

    void initDevNum();
    void updateDevNum(int num);

    void initLineNum();
    void updateLineNum(int num);

    void initVersion();
    void updateVersion(int num);

private slots:
    void on_serialBtn_clicked();
    void on_devNumBtn_clicked();
    void on_cmdBtn_clicked();
    void on_timeBtn_clicked();
    void on_vBtn_clicked();

    void on_lineBtn_clicked();

private:
    Ui::IP_SettingToolWid *ui;
    SerialPortDlg *mSerialPortDlg;
};

#endif // IP_SETTINGTOOLWID_H
