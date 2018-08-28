/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_simulationtoolwid.h"
#include "ui_z_simulationtoolwid.h"


Z_SimulationToolWid::Z_SimulationToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Z_SimulationToolWid)
{
    ui->setupUi(this);
}

Z_SimulationToolWid::~Z_SimulationToolWid()
{
    delete ui;
}

/**
 * @brief 开始模拟测试
 */
void Z_SimulationToolWid::startSimulateTest()
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    config->item->testMode = Z_Test_Simulate;
    emit simulateSig(Z_Test_Simulate);

    ui->mnTestBtn->setText(tr("停止测试"));
}

/**
 * @brief 停止模拟测试
 */
bool Z_SimulationToolWid::stopSimulateTest()
{
    bool ret = false;
    QuMsgBox box(this, tr("是否停止测试？？"));
    if(box.Exec()) {
        Z_ConfigFile *config = Z_ConfigFile::bulid();
        config->item->testMode = Z_Test_Stop;
        emit simulateSig(Z_Test_Stop);

        ret = true;
        ui->mnTestBtn->setText(tr("一键模拟"));
    }

    return ret;
}

void Z_SimulationToolWid::on_mnTestBtn_clicked()
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    int mode = config->item->testMode;

    switch (mode) {
    case Z_Test_Stop:
        startSimulateTest();
        break;

    case Z_Test_Simulate:
        stopSimulateTest();
        break;

    default:
        CriticalMsgBox box(this, tr("请停止其它操作!!"));
        break;
    }
}

void Z_SimulationToolWid::on_devBtn_clicked()
{
    emit simulateSig(Z_Info_Dev);
}

void Z_SimulationToolWid::on_transBtn_clicked()
{
    emit simulateSig(Z_Info_Trans);
}

void Z_SimulationToolWid::on_thresholdBtn_clicked()
{
    emit simulateSig(Z_Info_Threshold);
}

void Z_SimulationToolWid::on_envBtn_clicked()
{
    emit simulateSig(Z_Info_Env);
}

void Z_SimulationToolWid::on_outputBtn_clicked()
{
    emit simulateSig(Z_Info_Output);
}

void Z_SimulationToolWid::on_outputThresholdBtn_clicked()
{
    emit simulateSig(Z_Info_OutputThreshold);
}

void Z_SimulationToolWid::on_settingBtn_clicked()
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    int mode = config->item->testMode;
    if(mode == Z_Test_Simulate) {
        QuMsgBox box(this, tr("此操作会停止模拟测试，是否进入单项测试？？"));
        if(box.Exec())
            on_mnTestBtn_clicked();
        else
            return ;
    }
    emit simulateSig(Z_Info_Set);
}

void Z_SimulationToolWid::on_loopBtn_clicked()
{
     emit simulateSig(Z_Info_Loop);
}

void Z_SimulationToolWid::on_loopThresholdBtn_clicked()
{
    emit simulateSig(Z_Info_LoopThreshold);
}
