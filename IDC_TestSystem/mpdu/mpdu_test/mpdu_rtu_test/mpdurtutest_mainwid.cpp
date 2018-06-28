#include "mpdurtutest_mainwid.h"
#include "ui_mpdurtutest_mainwid.h"
#include "threshold/mpdurtutest_thresholdoutputwid.h"
#include "sw/mpdurtutest_swwid.h"
#include "ele/mpdurtutest_outputelewid.h"
#include "line/mpdurtutest_linewid.h"
#include "env/mpdurtutest_envwid.h"


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

QString MpduRtuTest_MainWid::getName(int mode)
{
    QString str = tr("输出位");

    switch (mode) {
    case Mpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Mpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Mpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    case Mpdu_Rtu_Test_max: str += tr("最大值"); break;
    case Mpdu_Rtu_Test_delay: str += tr("上下电延时"); break;
    default: break;
    }

    return str;
}


void MpduRtuTest_MainWid::initWid()
{
    MpduRtuTest_SwWid *swWid = new MpduRtuTest_SwWid(ui->tabWidget);
    ui->tabWidget->addTab(swWid, tr("输出位开关"));
    swWid->initwid(mSerialPort);

    for(int i=Mpdu_Rtu_Test_min; i<=Mpdu_Rtu_Test_delay; ++i) {
        MpduRtuTest_ThresholdOutputWid *wid = new MpduRtuTest_ThresholdOutputWid(ui->tabWidget);
        wid->initwid(i, mSerialPort);
        ui->tabWidget->addTab(wid, getName(i));
    }

    MpduRtuTest_OutputEleWid *outputEleWid = new MpduRtuTest_OutputEleWid(ui->tabWidget);
    ui->tabWidget->addTab(outputEleWid, tr("输出位电能清零"));
    outputEleWid->initwid(mSerialPort);

    MpduRtuTest_LineWid *lineWid = new MpduRtuTest_LineWid(ui->tabWidget);
    ui->tabWidget->addTab(lineWid, tr("相阈值设置"));
    lineWid->initWid(mSerialPort);

    MpduRtuTest_EnvWid *envWid = new MpduRtuTest_EnvWid(ui->tabWidget);
    ui->tabWidget->addTab(envWid, tr("传感器阈值设置"));
    envWid->initWid(mSerialPort);

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
