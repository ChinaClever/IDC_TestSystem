#ifndef Z_MODETOOLWID_H
#define Z_MODETOOLWID_H

#include "z_statustoolwid.h"

namespace Ui {
class Z_ModeToolWid;
}

class Z_ModeToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit Z_ModeToolWid(QWidget *parent = 0);
    ~Z_ModeToolWid();

signals:
    void simulateSig(int);

protected:
    bool initSerialPort();
    void updateSerialWid();
    void startTest();
    bool stopTest();

private slots:
    void on_serialBtn_clicked();
    void on_settingBtn_clicked();
    void on_testBtn_clicked();


    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Z_ModeToolWid *ui;
    SerialPortDlg *mSerialPortDlg;
};

#endif // Z_MODETOOLWID_H
