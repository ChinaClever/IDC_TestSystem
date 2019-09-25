/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "buslogstoolwid.h"
#include "ui_buslogstoolwid.h"

BusLogsToolWid::BusLogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BusLogsToolWid)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);

    initLogTime();
}

BusLogsToolWid::~BusLogsToolWid()
{
    delete ui;
}


/**
 * @brief 更新日志时间间隔
 * @param num
 */
void BusLogsToolWid::updateLogTime(int num)
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    config->item->logMins = num;

    ui->spinBox->setValue(num);
    config->setLogTime(num);
}

/**
 * @brief 初始化蛙声时间
 */
void BusLogsToolWid::initLogTime()
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    int num = config->getLogTime();
    updateLogTime(num);
}

void BusLogsToolWid::on_timeBtn_clicked()
{
    int time = ui->spinBox->value();
    updateLogTime(time);
}

void BusLogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(BUS_Log_Modbus);
}

void BusLogsToolWid::on_transBtn_clicked()
{
    emit logsSig(BUS_Log_Trans);
}

void BusLogsToolWid::on_envBtn_clicked()
{
    emit logsSig(BUS_Log_Env);
}

void BusLogsToolWid::on_recordBtn_clicked()
{
    emit logsSig(BUS_Log_Records);
}

void BusLogsToolWid::on_thresholdBtn_clicked()
{
    emit logsSig(BUS_Log_Threshold);
}

void BusLogsToolWid::on_alarmBtn_clicked()
{
    emit logsSig(BUS_Log_Alarm);
}

