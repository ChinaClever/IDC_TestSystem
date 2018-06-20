#include "mpdurtutest_mainwid.h"
#include "ui_mpdurtutest_mainwid.h"
#include "threshold/mpdurtutest_thresholdoutputwid.h"
#include "sw/mpdurtutest_swwid.h"

MpduRtuTest_MainWid::MpduRtuTest_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);

    mSerialPortDlg = new SerialPortDlg(this);
    mSerialPort = mSerialPortDlg->getSerialPort();

    initWid();
}

MpduRtuTest_MainWid::~MpduRtuTest_MainWid()
{
    delete ui;
}

void MpduRtuTest_MainWid::initWid()
{
    MpduRtuTest_SwWid *swWid = new MpduRtuTest_SwWid(ui->tabWidget);
    ui->tabWidget->addTab(swWid, tr("输出位开关"));
    swWid->initwid(mSerialPort);

    MpduRtuTest_ThresholdOutputWid *wid = new MpduRtuTest_ThresholdOutputWid(ui->tabWidget);
    wid->initwid(0, mSerialPort);
    ui->tabWidget->addTab(wid, tr("输出位最小值"));

    wid = new MpduRtuTest_ThresholdOutputWid(ui->tabWidget);
    wid->initwid(1, mSerialPort);
    ui->tabWidget->addTab(wid, tr("输出位最大值"));
}

void MpduRtuTest_MainWid::on_pushButton_clicked()
{
    mSerialPortDlg->exec();
    QString str = "---";
    if(mSerialPort->isOpened()) {
        str = mSerialPort->getSerialName();
    }
    ui->comLab->setText(str);
}
