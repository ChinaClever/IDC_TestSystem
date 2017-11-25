#ifndef SISETTINGTOOLWID_H
#define SISETTINGTOOLWID_H

#include <QWidget>
#include "serialportdlg.h"

namespace Ui {
class SiSettingToolWid;
}

class SiSettingToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit SiSettingToolWid(QWidget *parent = 0);
    ~SiSettingToolWid();

protected:
    void updateSerialWid();

    bool initSerialPort();

    void initLineNum();
    void updateLineNum(int num);

    void initDevNum();
    void updateDevNum(int num);

    void initDevCmd();
    void updateDevCmd(int num);

private slots:
    void on_serialBtn_clicked();

    void on_lineBtn_clicked();

    void on_devNumBtn_clicked();

    void on_cmdBtn_clicked();

private:
    Ui::SiSettingToolWid *ui;

    SerialPortDlg *mSerialPortDlg;
};

#endif // SISETTINGTOOLWID_H
