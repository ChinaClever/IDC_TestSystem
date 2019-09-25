/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_settingtoolwid.h"
#include "ui_eload_settingtoolwid.h"
#include "eload_com/eload_configfile.h"

ELoad_SettingToolWid::ELoad_SettingToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_SettingToolWid)
{
    ui->setupUi(this);
//    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
//    gridLayout->addWidget(this);

    initModbusTime();
    initDevCmd();
}

ELoad_SettingToolWid::~ELoad_SettingToolWid()
{
    delete ui;
}


/**
 * @brief 更新
 * @param num
 */
void ELoad_SettingToolWid::updateDevCmd(int num)
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    config->item->cmdModel = num;
    config->setModbusCmd(num);
}

void ELoad_SettingToolWid::initDevCmd()
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    int num = config->getModbusCmd();
    updateDevCmd(num);

    ui->cmdBox->setCurrentIndex(num-1);
}

void ELoad_SettingToolWid::on_cmdBtn_clicked()
{
    int num = ui->cmdBox->currentIndex();
    updateDevCmd(num+1);
}



/**
 * @brief 更新间隔时间
 * @param num
 */
void ELoad_SettingToolWid::updateModbusTime(int num)
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    config->item->msecs = 5*(num+1);
    config->setModbusTime(num);
}

void ELoad_SettingToolWid::initModbusTime()
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    int num = config->getModbusTime();
    updateModbusTime(num);
    ui->timeBox->setCurrentIndex(num);
}

void ELoad_SettingToolWid::on_timeBtn_clicked()
{
    updateModbusTime(ui->timeBox->currentIndex());
}

