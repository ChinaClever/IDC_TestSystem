/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_settingtoolwid.h"
#include "ui_z_settingtoolwid.h"

Z_SettingToolWid::Z_SettingToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Z_SettingToolWid)
{
    ui->setupUi(this);
    initModbusTime();
    initDevCmd();
    initDevNum();
}

Z_SettingToolWid::~Z_SettingToolWid()
{
    delete ui;
}


/**
 * @brief 更新
 * @param num
 */
void Z_SettingToolWid::updateDevCmd(int num)
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    config->item->cmdModel = num;
    config->setModbusCmd(num);
}

void Z_SettingToolWid::initDevCmd()
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    int num = config->getModbusCmd();
    updateDevCmd(num);

    ui->cmdBox->setCurrentIndex(num-1);
}

void Z_SettingToolWid::on_cmdBtn_clicked()
{
    int num = ui->cmdBox->currentIndex();
    updateDevCmd(num+1);
}



/**
 * @brief 更新间隔时间
 * @param num
 */
void Z_SettingToolWid::updateModbusTime(int num)
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    config->item->msecs = 5*(num+1);
    config->setModbusTime(num);
}

void Z_SettingToolWid::initModbusTime()
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    int num = config->getModbusTime();
    updateModbusTime(num);
    ui->timeBox->setCurrentIndex(num);
}

void Z_SettingToolWid::on_timeBtn_clicked()
{
    updateModbusTime(ui->timeBox->currentIndex());
}


/**
 * @brief 更新设备数量
 * @param num
 */
void Z_SettingToolWid::updateDevNum(int num)
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    config->item->devNum = num;
    config->setDevNum(num);
}

void Z_SettingToolWid::initDevNum()
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    int num = config->getDevNum();;
    updateDevNum(num);
    ui->spinBox->setValue(num);
}


void Z_SettingToolWid::on_devNumBtn_clicked()
{
    updateDevNum(ui->spinBox->value());
}

