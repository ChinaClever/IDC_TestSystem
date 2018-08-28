/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_simulationtoolwid.h"
#include "ui_ip_simulationtoolwid.h"

IP_SimulationToolWid::IP_SimulationToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IP_SimulationToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

IP_SimulationToolWid::~IP_SimulationToolWid()
{
    delete ui;
}



/**
 * @brief 开始模拟测试
 */
void IP_SimulationToolWid::startSimulateTest()
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    config->item->testMode = IP_Test_Simulate;
    emit simulateSig(IP_Test_Simulate);

    ui->mnTestBtn->setText(tr("停止测试"));
}

/**
 * @brief 停止模拟测试
 */
bool IP_SimulationToolWid::stopSimulateTest()
{
    bool ret = false;
    QuMsgBox box(this, tr("是否停止测试？？"));
    if(box.Exec()) {
        IP_ConfigFile *config = IP_ConfigFile::bulid();
        config->item->testMode = IP_Test_Stop;
        emit simulateSig(IP_Test_Stop);

        ret = true;
        ui->mnTestBtn->setText(tr("一键模拟"));
    }

    return ret;
}

void IP_SimulationToolWid::on_mnTestBtn_clicked()
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    int mode = config->item->testMode;

    switch (mode) {
    case IP_Test_Stop:
        startSimulateTest();
        break;

    case IP_Test_Simulate:
        stopSimulateTest();
        break;

    default:
        CriticalMsgBox box(this, tr("请停止其它操作!!"));
        break;
    }
}

void IP_SimulationToolWid::on_devBtn_clicked()
{
    emit simulateSig(IP_Info_Dev);
}

void IP_SimulationToolWid::on_transBtn_clicked()
{
    emit simulateSig(IP_Info_Trans);
}

void IP_SimulationToolWid::on_thresholdBtn_clicked()
{
    emit simulateSig(IP_Info_Threshold);
}

void IP_SimulationToolWid::on_envBtn_clicked()
{
    emit simulateSig(IP_Info_Env);
}

void IP_SimulationToolWid::on_settingBtn_clicked()
{

}
