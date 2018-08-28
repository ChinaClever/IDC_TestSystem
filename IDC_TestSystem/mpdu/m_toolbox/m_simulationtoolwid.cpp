/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_simulationtoolwid.h"
#include "ui_m_simulationtoolwid.h"

M_SimulationToolWid::M_SimulationToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::M_SimulationToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

M_SimulationToolWid::~M_SimulationToolWid()
{
    delete ui;
}

/**
 * @brief 开始模拟测试
 */
void M_SimulationToolWid::startSimulateTest()
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    config->item->testMode = M_Test_Simulate;
    emit simulateSig(M_Test_Simulate);

    ui->mnTestBtn->setText(tr("停止测试"));
}

/**
 * @brief 停止模拟测试
 */
bool M_SimulationToolWid::stopSimulateTest()
{
    bool ret = false;
    QuMsgBox box(this, tr("是否停止测试？？"));
    if(box.Exec()) {
        M_ConfigFile *config = M_ConfigFile::bulid();
        config->item->testMode = M_Test_Stop;
        emit simulateSig(M_Test_Stop);

        ret = true;
        ui->mnTestBtn->setText(tr("一键模拟"));
    }

    return ret;
}

void M_SimulationToolWid::on_mnTestBtn_clicked()
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    int mode = config->item->testMode;

    switch (mode) {
    case M_Test_Stop:
        startSimulateTest();
        break;

    case M_Test_Simulate:
        stopSimulateTest();
        break;

    default:
        CriticalMsgBox box(this, tr("请停止其它操作!!"));
        break;
    }
}

void M_SimulationToolWid::on_devBtn_clicked()
{
    emit simulateSig(M_Info_Dev);
}

void M_SimulationToolWid::on_transBtn_clicked()
{
    emit simulateSig(M_Info_Trans);
}

void M_SimulationToolWid::on_thresholdBtn_clicked()
{
    emit simulateSig(M_Info_Threshold);
}

void M_SimulationToolWid::on_envBtn_clicked()
{
    emit simulateSig(M_Info_Env);
}

void M_SimulationToolWid::on_outputBtn_clicked()
{
    emit simulateSig(M_Info_Output);
}

void M_SimulationToolWid::on_outputThresholdBtn_clicked()
{
    emit simulateSig(M_Info_OutputThreshold);
}

void M_SimulationToolWid::on_settingBtn_clicked()
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    int mode = config->item->testMode;
    if(mode == M_Test_Simulate) {
        QuMsgBox box(this, tr("此操作会停止模拟测试，是否进入单项测试？？"));
        if(box.Exec())
            on_mnTestBtn_clicked();
        else
            return ;
    }
    emit simulateSig(M_Info_Set);
}
