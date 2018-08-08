/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_settingtoolwid.h"
#include "ui_ip_settingtoolwid.h"

IP_SettingToolWid::IP_SettingToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IP_SettingToolWid)
{
    ui->setupUi(this);
    mSerialPortDlg = new SerialPortDlg(this);

    initSerialPort();
    initModbusTime();
    initDevCmd();
    initDevNum();
    initVersion();
}

IP_SettingToolWid::~IP_SettingToolWid()
{
    delete ui;
}

/**
 * @brief 初始化串口
 * @return
 */
bool IP_SettingToolWid::initSerialPort()
{
    bool ret = false;

    IP_ConfigFile *config = IP_ConfigFile::bulid();
    SerialPort *serial = mSerialPortDlg->getSerialPort();
    config->item->serial = serial;

    QString com = config->getSerialName();
    if(!com.isEmpty())
    {
        ret = serial->isContains(com);
        if(ret) {
            ret = serial->open(com);
            updateSerialWid();
        }
    }

    return ret;
}

/**
 * @brief 更新串口窗口
 */
void IP_SettingToolWid::updateSerialWid()
{
    QPalette pe;
    SerialPort *serial = mSerialPortDlg->getSerialPort();
    QString str = serial->getSerialName();

    if(serial->isOpened()) {
        IP_ConfigFile::bulid()->setSerialName(str);
        str += tr(" 已打开");
        pe.setColor(QPalette::WindowText,Qt::black);
    } else {
        str += tr(" 串口未打开");
        pe.setColor(QPalette::WindowText,Qt::red);
    }

    ui->serialLab->setText(str);
    ui->serialLab->setPalette(pe);
}

void IP_SettingToolWid::on_serialBtn_clicked()
{
    mSerialPortDlg->exec();
    updateSerialWid();
}


/**
 * @brief 更新
 * @param num
 */
void IP_SettingToolWid::updateDevCmd(int num)
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    config->item->cmdModel = num;
    config->setModbusCmd(num);
}

void IP_SettingToolWid::initDevCmd()
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    int num = config->getModbusCmd();
    updateDevCmd(num);

    ui->cmdBox->setCurrentIndex(num-1);
}

void IP_SettingToolWid::on_cmdBtn_clicked()
{
    int num = ui->cmdBox->currentIndex();
    updateDevCmd(num+1);
}



/**
 * @brief 更新间隔时间
 * @param num
 */
void IP_SettingToolWid::updateModbusTime(int num)
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    config->item->msecs = 5*(num+1);
    config->setModbusTime(num);
}

void IP_SettingToolWid::initModbusTime()
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    int num = config->getModbusTime();
    updateModbusTime(num);
    ui->timeBox->setCurrentIndex(num);
}

void IP_SettingToolWid::on_timeBtn_clicked()
{
    updateModbusTime(ui->timeBox->currentIndex());
}


/**
 * @brief 更新设备数量
 * @param num
 */
void IP_SettingToolWid::updateDevNum(int num)
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    config->item->devNum = num;
    config->setDevNum(num);
}

void IP_SettingToolWid::initDevNum()
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    int num = config->getDevNum();;
    updateDevNum(num);
    ui->spinBox->setValue(num);
}


void IP_SettingToolWid::on_devNumBtn_clicked()
{
    updateDevNum(ui->spinBox->value());
}

void IP_SettingToolWid::updateVersion(int num)
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    config->item->v = num;
    config->setVersion(num);
}

void IP_SettingToolWid::initVersion()
{
    IP_ConfigFile *config = IP_ConfigFile::bulid();
    int num = config->getVersion();;
    updateVersion(num);
    ui->vBox->setCurrentIndex(num);
}

void IP_SettingToolWid::on_vBtn_clicked()
{
    updateVersion(ui->vBox->currentIndex());
}


