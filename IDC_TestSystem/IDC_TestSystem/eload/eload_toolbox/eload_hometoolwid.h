#ifndef ELOAD_HOMETOOLWID_H
#define ELOAD_HOMETOOLWID_H

#include "eload_com/eload_configfile.h"

namespace Ui {
class ELoad_HomeToolWid;
}

class ELoad_HomeToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_HomeToolWid(QWidget *parent = 0);
    ~ELoad_HomeToolWid();

signals:
    void toolSig(int);
    void saveSig();


protected:
    bool initSerialPort();
    void updateSerialWid();
    void initDevNum();
    void updateDevNum(int num);

private slots:
    void on_homeBtn_clicked();
    void on_serialBtn_clicked();
    void on_devNumBtn_clicked();
    void on_temriseBtn_clicked();

private:
    Ui::ELoad_HomeToolWid *ui;
    SerialPortDlg *mSerialPortDlg;
};

#endif // ELOAD_HOMETOOLWID_H
