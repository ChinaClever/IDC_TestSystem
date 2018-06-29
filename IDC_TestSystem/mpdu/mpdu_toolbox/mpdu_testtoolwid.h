#ifndef MPDU_TESTTOOLWID_H
#define MPDU_TESTTOOLWID_H

#include "serialportdlg.h"

namespace Ui {
class Mpdu_TestToolWid;
}

class Mpdu_TestToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit Mpdu_TestToolWid(QWidget *parent = 0);
    ~Mpdu_TestToolWid();

private slots:
    void on_serialBtn_clicked();

private:
    Ui::Mpdu_TestToolWid *ui;
     SerialPortDlg *mSerialPortDlg;
};

#endif // MPDU_TESTTOOLWID_H
