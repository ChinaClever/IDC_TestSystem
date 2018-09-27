#include "testserialnumdlg.h"
#include "ui_testserialnumdlg.h"

TestSerialNumDlg::TestSerialNumDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestSerialNumDlg)
{
    ui->setupUi(this);
    com_setBackColour(tr("请输入被测模块序列号"), this);
    initWid();
}

TestSerialNumDlg::~TestSerialNumDlg()
{
    delete ui;
}

void TestSerialNumDlg::initWid()
{
    mTestConfig = new TestConfig();
    mItem = mTestConfig->serialNumitem;
    ui->dateEdit->setDate(QDate::currentDate());

    ui->opLineEdit->setText(mItem->op);
    ui->cnLineEdit->setText(mItem->cn);
    ui->barCodeLineEdit->setText(mItem->barCode);
    ui->batchComboBox->setCurrentText(mItem->batch);
    ui->purposeComboBox->setCurrentText(mItem->purpose);
    ui->clearRadioButton->setChecked(mItem->snClear);
}

sSerialNumItem *TestSerialNumDlg::getSerialNum()
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

    return mItem;
}

void TestSerialNumDlg::on_batchComboBox_currentTextChanged(const QString &arg1)
{
    QString str = ui->purposeComboBox->currentText() +"_" + arg1;
    ui->statusLab->setText(str);
}

void TestSerialNumDlg::on_purposeComboBox_currentTextChanged(const QString &arg1)
{
    QString str = arg1 + "_" + ui->batchComboBox->currentText();
    ui->statusLab->setText(str);
}


bool TestSerialNumDlg::inputCheck()
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
            mItem->sn = str;
        }
    }

    str = ui->opLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入操作员!!!"));
        return false;
    } else {
        mItem->op = str;
    }

    str = ui->cnLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入电脑号!!!"));
        return false;
    } else {
        mItem->cn = str;
    }

    str = ui->barCodeLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入工装条码!!!"));
        return false;
    } else {
        mItem->barCode = str;
    }

    mItem->date = ui->dateEdit->date();
    mItem->batch = ui->batchComboBox->currentText();
    mItem->name = ui->typeComboBox->currentText();
    mItem->purpose = ui->purposeComboBox->currentText();
    mItem->snClear = ui->clearRadioButton->isChecked();
    mItem->errStop = ui->errStopCheckBox->isChecked();
    mItem->isSave = ui->saveCheckBox->isChecked();

    return true;
}

void TestSerialNumDlg::on_okBtn_clicked()
{
    bool ret = inputCheck();
    if(ret) {
        this->accepted();
    }
}

void TestSerialNumDlg::on_cancelBtn_clicked()
{
    this->close();
}