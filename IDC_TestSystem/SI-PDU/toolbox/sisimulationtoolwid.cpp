/*
 * Si 模拟窗口
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sisimulationtoolwid.h"
#include "ui_sisimulationtoolwid.h"
#include "si_com/siconfigfile.h"
#include <QGridLayout>

SiSimulationToolWid::SiSimulationToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiSimulationToolWid)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->addWidget(this);
//    com_setBackColour("",this);
}

SiSimulationToolWid::~SiSimulationToolWid()
{
    delete ui;
}

/**
 * @brief 开始模拟测试
 */
void SiSimulationToolWid::startSimulateTest()
{
    SiConfigFile *config = SiConfigFile::bulid();
    config->item->testMode = SI_Test_Simulate;
    emit simulateSig(SI_Test_Simulate);

    ui->mnTestBtn->setText(tr("停止测试"));
}

/**
 * @brief 停止模拟测试
 */
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

void SiSimulationToolWid::on_envBtn_clicked()
{
    emit simulateSig(SI_Env_Info);
}

void SiSimulationToolWid::on_thresholdBtn_clicked()
{
     emit simulateSig(SI_Threshold_Info);
}

void SiSimulationToolWid::on_transBtn_clicked()
{
     emit simulateSig(SI_Trans_Info);
}

void SiSimulationToolWid::on_realBtn_clicked()
{
     emit simulateSig(SI_DevReal_Info);
}
