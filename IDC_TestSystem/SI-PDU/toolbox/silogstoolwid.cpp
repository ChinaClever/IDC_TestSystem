/*
 * Si 日志窗口
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "silogstoolwid.h"
#include "ui_silogstoolwid.h"
#include "si_com/siconfigfile.h"
#include "silogstimetooldlg.h"

SiLogsToolWid::SiLogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiLogsToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    initLogTime();
}

SiLogsToolWid::~SiLogsToolWid()
{
    delete ui;
}

void SiLogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(Log_Modbus);
}


/**
 * @brief 更新日志时间间隔
 * @param num
 */
void SiLogsToolWid::updateLogTime(int num)
{
    SiConfigFile *config = SiConfigFile::bulid();
    config->item->logMins = num;

    QString str = QString::number(config->item->logMins) + tr("分钟");
    ui->timeLab->setText(str);
    config->setLogTime(num);
}

/**
 * @brief 初始化蛙声时间
 */
void SiLogsToolWid::initLogTime()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->getLogTime();
    updateLogTime(num);
}

void SiLogsToolWid::on_timeBtn_clicked()
{
    SiLogsTimeToolDlg dlg(this);
    if(dlg.exec() == QDialog::Accepted) {
        int time = dlg.getTime();
        updateLogTime(time);
    }
}

void SiLogsToolWid::on_transBtn_clicked()
{
    emit logsSig(Log_Trans);
}

void SiLogsToolWid::on_envBtn_clicked()
{
     emit logsSig(Log_Env);
}

void SiLogsToolWid::on_recordBtn_clicked()
{
     emit logsSig(Log_Line);
}

void SiLogsToolWid::on_thresholdBtn_clicked()
{
    emit logsSig(Log_LineThreshold);
}

void SiLogsToolWid::on_alarmBtn_clicked()
{
     emit logsSig(Log_Alarm);
}
