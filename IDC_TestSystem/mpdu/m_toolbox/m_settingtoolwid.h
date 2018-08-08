#ifndef M_SETTINGTOOLWID_H
#define M_SETTINGTOOLWID_H

#include "m_logstoolwid.h"

namespace Ui {
class M_SettingToolWid;
}

class M_SettingToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit M_SettingToolWid(QWidget *parent = 0);
    ~M_SettingToolWid();

protected:
    bool initSerialPort();
    void updateSerialWid();

    void initModbusTime();
    void updateModbusTime(int num);

    void initDevCmd();
    void updateDevCmd(int num);

    void initDevNum();
    void updateDevNum(int num);

    void initOutputNum();
    void updateOutputNum(int num);

private slots:
    void on_serialBtn_clicked();
    void on_devNumBtn_clicked();
    void on_outputNumBtn_clicked();
    void on_cmdBtn_clicked();
    void on_timeBtn_clicked();

private:
    Ui::M_SettingToolWid *ui;
    SerialPortDlg *mSerialPortDlg;
};

#endif // M_SETTINGTOOLWID_H
