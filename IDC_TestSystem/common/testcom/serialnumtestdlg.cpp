#include "serialnumtestdlg.h"
#include "ui_serialnumtestdlg.h"

SerialNumTestDlg::SerialNumTestDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialNumTestDlg)
{
    ui->setupUi(this);
    com_setBackColour(tr("请输入被测模块序列号"), this);
    ui->dateEdit->setDate(QDate::currentDate());
}

SerialNumTestDlg::~SerialNumTestDlg()
{
    delete ui;
}

sSerialNum SerialNumTestDlg::getSerialNum()
{
    bool ret = inputCheck();
    if(ret) {
        ret = ui->addRadioButton->isChecked();
        if(ret) {
            int data = ui->snLineEdit->text().toInt() + 1;
            QString str = QString::number(data);
            ui->snLineEdit->setText(str);
        } else {
            ui->snLineEdit->clear();
        }
    }

    return mSerialNum;
}

void SerialNumTestDlg::on_batchComboBox_currentTextChanged(const QString &arg1)
{
    QString str = ui->purposeComboBox->currentText() +"_" + arg1;
    ui->statusLab->setText(str);
}

void SerialNumTestDlg::on_purposeComboBox_currentTextChanged(const QString &arg1)
{
    QString str = arg1 + "_" + ui->batchComboBox->currentText();
    ui->statusLab->setText(str);
}

bool SerialNumTestDlg::inputCheck()
{
    bool ret = false;
    QString str = ui->snLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入产品条码"));
        return false;
    } else {
        ret = cm_isDigitStr(str);
        if(!ret) {
             CriticalMsgBox box(this, tr("产品条码应是纯数字，请重新输入!!"));
             return false;
        } else {
            mSerialNum.sn = str;
        }
    }

    str = ui->opLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入操作员!!!"));
        return false;
    } else {
        mSerialNum.op = str;
    }

    str = ui->cnLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入电脑号!!!"));
        return false;
    } else {
        mSerialNum.cn = str;
    }

    str = ui->barCodeLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入工装条码!!!"));
        return false;
    } else {
        mSerialNum.barCode = str;
    }

    mSerialNum.date = ui->dateEdit->date();
    mSerialNum.batch = ui->batchComboBox->currentText();
    mSerialNum.name = ui->typeComboBox->currentText();
    mSerialNum.purpose = ui->purposeComboBox->currentText();
    mSerialNum.snClear = ui->clearRadioButton->isChecked();
    mSerialNum.errStop = ui->errStopCheckBox->isChecked();
    mSerialNum.isSave = ui->saveCheckBox->isChecked();

    return true;
}

void SerialNumTestDlg::on_okBtn_clicked()
{
    bool ret = inputCheck();
    if(ret) {
        this->accepted();
    }
}

void SerialNumTestDlg::on_cancelBtn_clicked()
{
    this->close();
}
