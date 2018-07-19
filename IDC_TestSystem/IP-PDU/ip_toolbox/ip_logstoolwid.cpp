/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_logstoolwid.h"
#include "ui_ip_logstoolwid.h"

IP_LogsToolWid::IP_LogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IP_LogsToolWid)
{
    ui->setupUi(this);
    initLogTime();
}

IP_LogsToolWid::~IP_LogsToolWid()
{
    delete ui;
}


/**
 * @brief 更新日志时间间隔
 * @param num
 */
void IP_LogsToolWid::updateLogTime(int num)
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    config->item->logMins = num;

    ui->spinBox->setValue(num);
    config->setLogTime(num);
}

/**
 * @brief 初始化蛙声时间
 */
void IP_LogsToolWid::initLogTime()
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    int num = config->getLogTime();
    updateLogTime(num);
}

void IP_LogsToolWid::on_timeBtn_clicked()
{
    int time = ui->spinBox->value();
    updateLogTime(time);
}


void IP_LogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(IP_Log_Modbus);
}

void IP_LogsToolWid::on_transBtn_clicked()
{
    emit logsSig(IP_Log_Trans);
}

void IP_LogsToolWid::on_envBtn_clicked()
{
    emit logsSig(IP_Log_Env);
}

void IP_LogsToolWid::on_recordBtn_clicked()
{
    emit logsSig(IP_Log_Records);
}

void IP_LogsToolWid::on_thresholdBtn_clicked()
{
    emit logsSig(IP_Log_Threshold);
}

void IP_LogsToolWid::on_alarmBtn_clicked()
{
    emit logsSig(IP_Log_Alarm);
}



