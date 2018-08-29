/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_logstoolwid.h"
#include "ui_z_logstoolwid.h"

Z_LogsToolWid::Z_LogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Z_LogsToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

Z_LogsToolWid::~Z_LogsToolWid()
{
    delete ui;
}

/**
 * @brief 更新日志时间间隔
 * @param num
 */
void Z_LogsToolWid::updateLogTime(int num)
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    config->item->logMins = num;

    ui->spinBox->setValue(num);
    config->setLogTime(num);
}

/**
 * @brief 初始化蛙声时间
 */
void Z_LogsToolWid::initLogTime()
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    int num = config->getLogTime();
    updateLogTime(num);
}

void Z_LogsToolWid::on_timeBtn_clicked()
{
    int time = ui->spinBox->value();
    updateLogTime(time);
}


void Z_LogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(Z_Log_Modbus);
}

void Z_LogsToolWid::on_transBtn_clicked()
{
    emit logsSig(Z_Log_Trans);
}

void Z_LogsToolWid::on_envBtn_clicked()
{
    emit logsSig(Z_Log_Env);
}

void Z_LogsToolWid::on_recordBtn_clicked()
{
    emit logsSig(Z_Log_Records);
}

void Z_LogsToolWid::on_thresholdBtn_clicked()
{
    emit logsSig(Z_Log_Threshold);
}

void Z_LogsToolWid::on_alarmBtn_clicked()
{
    emit logsSig(Z_Log_Alarm);
}

void Z_LogsToolWid::on_outputBtn_clicked()
{
    emit logsSig(Z_Log_Output);
}

void Z_LogsToolWid::on_loopBtn_clicked()
{
    emit logsSig(Z_Log_Loop);
}
