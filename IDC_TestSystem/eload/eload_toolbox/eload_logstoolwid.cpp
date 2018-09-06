#include "eload_logstoolwid.h"
#include "ui_eload_logstoolwid.h"
#include "eload_com/eload_configfile.h"

ELoad_LogsToolWid::ELoad_LogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_LogsToolWid)
{
    ui->setupUi(this);
}

ELoad_LogsToolWid::~ELoad_LogsToolWid()
{
    delete ui;
}


/**
 * @brief 更新日志时间间隔
 * @param num
 */
void ELoad_LogsToolWid::updateLogTime(int num)
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    config->item->logMins = num;

    ui->spinBox->setValue(num);
    config->setLogTime(num);
}

/**
 * @brief 初始化蛙声时间
 */
void ELoad_LogsToolWid::initLogTime()
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    int num = config->getLogTime();
    updateLogTime(num);
}

void ELoad_LogsToolWid::on_timeBtn_clicked()
{
    int time = ui->spinBox->value();
    updateLogTime(time);
}


void ELoad_LogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(ELoad_Log_Modbus);
}

void ELoad_LogsToolWid::on_transBtn_clicked()
{
    emit logsSig(ELoad_Log_Trans);
}

void ELoad_LogsToolWid::on_envBtn_clicked()
{
    emit logsSig(ELoad_Log_Env);
}

void ELoad_LogsToolWid::on_thresholdBtn_clicked()
{
    emit logsSig(ELoad_Log_Threshold);
}

void ELoad_LogsToolWid::on_alarmBtn_clicked()
{
    emit logsSig(ELoad_Log_Alarm);
}

void ELoad_LogsToolWid::on_outputBtn_clicked()
{
    emit logsSig(ELoad_Log_Output);
}

