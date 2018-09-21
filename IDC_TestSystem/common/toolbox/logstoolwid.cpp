#include "logstoolwid.h"
#include "ui_logstoolwid.h"

LogsToolWid::LogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogsToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

LogsToolWid::~LogsToolWid()
{
    delete ui;
}

void LogsToolWid::mpdu()
{
    ui->loopBtn->setHidden(true);
}

void LogsToolWid::sipdu()
{
    mpdu();
    ui->outputBtn->setHidden(true);
}
/**
 * @brief 更新日志时间间隔
 * @param num
 */
void LogsToolWid::updateLogTime(int num)
{
    mConfig->item->logMins = num;

    ui->spinBox->setValue(num);
    mConfig->setLogTime(num);
}

/**
 * @brief 初始化蛙声时间
 */
void LogsToolWid::initLogTime()
{
    int num = mConfig->getLogTime();
    updateLogTime(num);
}

void LogsToolWid::on_timeBtn_clicked()
{
    int time = ui->spinBox->value();
    updateLogTime(time);
}


void LogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(Log_Modbus);
}

void LogsToolWid::on_transBtn_clicked()
{
    emit logsSig(Log_Trans);
}

void LogsToolWid::on_envBtn_clicked()
{
    emit logsSig(Log_Env);
}

void LogsToolWid::on_recordBtn_clicked()
{
    emit logsSig(Log_Line);
}

void LogsToolWid::on_thresholdBtn_clicked()
{
    emit logsSig(Log_LineThreshold);
}

void LogsToolWid::on_alarmBtn_clicked()
{
    emit logsSig(Log_Alarm);
}

void LogsToolWid::on_outputBtn_clicked()
{
    emit logsSig(Log_Output);
}

void LogsToolWid::on_loopBtn_clicked()
{
    emit logsSig(Log_Loop);
}
