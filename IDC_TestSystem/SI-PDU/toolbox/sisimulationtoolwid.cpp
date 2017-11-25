#include "sisimulationtoolwid.h"
#include "ui_sisimulationtoolwid.h"
#include "si_com/siconfigfile.h"

SiSimulationToolWid::SiSimulationToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiSimulationToolWid)
{
    ui->setupUi(this);
}

SiSimulationToolWid::~SiSimulationToolWid()
{
    delete ui;
}

void SiSimulationToolWid::startSimulateTest()
{
    SiConfigFile *config = SiConfigFile::bulid();
    config->item->testMode = SI_Test_Simulate;
    emit simulateSig(SI_Test_Simulate);

    ui->mnTestBtn->setText(tr("停止测试"));
}

void SiSimulationToolWid::stopSimulateTest()
{
    QuMsgBox box(this, tr("是否停止测试？？"));
    if(box.Exec()) {
        SiConfigFile *config = SiConfigFile::bulid();
        config->item->testMode = SI_Test_Stop;
        emit simulateSig(SI_Test_Stop);

        ui->mnTestBtn->setText(tr("一键模拟"));
    }
}

void SiSimulationToolWid::on_mnTestBtn_clicked()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int mode = config->item->testMode;

    switch (mode) {
    case SI_Test_Stop:
        startSimulateTest();
        break;

    case SI_Test_Simulate:
        stopSimulateTest();
        break;

    default:
        CriticalMsgBox box(this, tr("请停止其它操作!!"));
        break;
    }

}
