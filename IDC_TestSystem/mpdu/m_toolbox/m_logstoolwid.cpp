/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_logstoolwid.h"
#include "ui_m_logstoolwid.h"

M_LogsToolWid::M_LogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::M_LogsToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

M_LogsToolWid::~M_LogsToolWid()
{
    delete ui;
}



/**
 * @brief 更新日志时间间隔
 * @param num
 */
void M_LogsToolWid::updateLogTime(int num)
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    config->item->logMins = num;

    ui->spinBox->setValue(num);
    config->setLogTime(num);
}

/**
 * @brief 初始化蛙声时间
 */
void M_LogsToolWid::initLogTime()
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    int num = config->getLogTime();
    updateLogTime(num);
}

void M_LogsToolWid::on_timeBtn_clicked()
{
    int time = ui->spinBox->value();
    updateLogTime(time);
}


void M_LogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(M_Log_Modbus);
}

void M_LogsToolWid::on_transBtn_clicked()
{
    emit logsSig(M_Log_Trans);
}

void M_LogsToolWid::on_envBtn_clicked()
{
    emit logsSig(M_Log_Env);
}

void M_LogsToolWid::on_recordBtn_clicked()
{
    emit logsSig(M_Log_Records);
}

void M_LogsToolWid::on_thresholdBtn_clicked()
{
    emit logsSig(M_Log_Threshold);
}

void M_LogsToolWid::on_alarmBtn_clicked()
{
    emit logsSig(M_Log_Alarm);
}

void M_LogsToolWid::on_outputBtn_clicked()
{
    emit logsSig(M_Log_Output);
}
