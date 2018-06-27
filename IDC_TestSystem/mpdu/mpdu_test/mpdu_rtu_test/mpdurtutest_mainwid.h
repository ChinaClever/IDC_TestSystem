#ifndef MPDURTUTEST_MAINWID_H
#define MPDURTUTEST_MAINWID_H

#include "serialportdlg.h"

namespace Ui {
class MpduRtuTest_MainWid;
}

class MpduRtuTest_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_MainWid(QWidget *parent = 0);
    ~MpduRtuTest_MainWid();

protected:
    void initWid();
    QString getName(int mode);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MpduRtuTest_MainWid *ui;

    SerialPortDlg *mSerialPortDlg;
    SerialPort *mSerialPort;
};

#endif // MPDURTUTEST_MAINWID_H
