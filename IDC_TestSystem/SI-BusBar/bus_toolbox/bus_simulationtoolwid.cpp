/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_simulationtoolwid.h"
#include "ui_bus_simulationtoolwid.h"

BUS_SimulationToolWid::BUS_SimulationToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_SimulationToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

BUS_SimulationToolWid::~BUS_SimulationToolWid()
{
    delete ui;
}



/**
 * @brief 开始模拟测试
 */
void BUS_SimulationToolWid::startSimulateTest()
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    config->item->testMode = BUS_Test_Simulate;
    emit simulateSig(BUS_Test_Simulate);

    ui->mnTestBtn->setText(tr("停止测试"));
}

/**
 * @brief 停止模拟测试
 */
bool BUS_SimulationToolWid::stopSimulateTest()
{
    bool ret = false;
    QuMsgBox box(this, tr("是否停止测试？？"));
    if(box.Exec()) {
        BUS_ConfigFile *config = BUS_ConfigFile::bulid();
        config->item->testMode = BUS_Test_Stop;
        emit simulateSig(BUS_Test_Stop);

        ret = true;
        ui->mnTestBtn->setText(tr("一键模拟"));
    }

    return ret;
}

void BUS_SimulationToolWid::on_mnTestBtn_clicked()
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    int mode = config->item->testMode;

    switch (mode) {
    case BUS_Test_Stop:
        startSimulateTest();
        break;

    case BUS_Test_Simulate:
        stopSimulateTest();
        break;

    default:
        CriticalMsgBox box(this, tr("请停止其它操作!!"));
        break;
    }
}

void BUS_SimulationToolWid::on_busBtn_clicked()
{
    emit simulateSig(BUS_Info_Bus);
}

void BUS_SimulationToolWid::on_boxBtn_clicked()
{
    emit simulateSig(BUS_Info_Box);
}

void BUS_SimulationToolWid::on_loopBtn_clicked()
{
    emit simulateSig(BUS_Info_Loop);
}

void BUS_SimulationToolWid::on_transBtn_clicked()
{
    emit simulateSig(BUS_Info_Trans);
}

void BUS_SimulationToolWid::on_thresholdBtn_clicked()
{
    emit simulateSig(BUS_Info_Threshold);
}

void BUS_SimulationToolWid::on_envBtn_clicked()
{
    emit simulateSig(BUS_Info_Env);
}

