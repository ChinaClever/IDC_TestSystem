#include "serialportdlg.h"
#include "ui_serialportdlg.h"

SerialPortDlg::SerialPortDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortDlg)
{
    ui->setupUi(this);
    serial = new SerialPortWid(this);
}

SerialPortDlg::~SerialPortDlg()
{
    delete ui;
}
