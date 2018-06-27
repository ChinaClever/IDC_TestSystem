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

QString MpduRtuTest_MainWid::getName(int mode)
{
    QString str = tr("输出位");

    switch (mode) {
    case Mpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Mpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Mpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    case Mpdu_Rtu_Test_max: str += tr("最大值"); break;
    default: break;
    }

    return str;
}


void MpduRtuTest_MainWid::initWid()
{
    MpduRtuTest_SwWid *swWid = new MpduRtuTest_SwWid(ui->tabWidget);
    ui->tabWidget->addTab(swWid, tr("输出位开关"));
    swWid->initwid(mSerialPort);

    for(int i=Mpdu_Rtu_Test_min; i<=Mpdu_Rtu_Test_max; ++i) {
        MpduRtuTest_ThresholdOutputWid *wid = new MpduRtuTest_ThresholdOutputWid(ui->tabWidget);
        wid->initwid(i, mSerialPort);
        ui->tabWidget->addTab(wid, getName(i));
    }
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
