#include "serialnumtestdlg.h"
#include "ui_serialnumtestdlg.h"

SerialNumTestDlg::SerialNumTestDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialNumTestDlg)
{
    ui->setupUi(this);
    com_setBackColour(tr("请输入被测模块序列号"), this);

}

SerialNumTestDlg::~SerialNumTestDlg()
{
    delete ui;
}
