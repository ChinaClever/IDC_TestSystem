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
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    mSerialPortDlg = new SerialPortDlg(this);

    initSerialPort();
    initModbusTime();
    initDevCmd();
    initDevNum();
}

ELoad_SettingToolWid::~ELoad_SettingToolWid()
{
    delete ui;
}

/**
 * @brief 初始化串口
 * @return
 */
bool ELoad_SettingToolWid::initSerialPort()
{
    bool ret = false;

    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    SerialPort *serial = mSerialPortDlg->getSerialPort();
    config->item->serial = serial;

    QString com = config->getSerialName();
    if(!com.isEmpty())
    {
        ret = serial->isContains(com);
        if(ret) {
//            ret = serial->open(com);
            updateSerialWid();
        }
    }

    return ret;
}

/**
 * @brief 更新串口窗口
 */
void ELoad_SettingToolWid::updateSerialWid()
{
    QPalette pe;
    SerialPort *serial = mSerialPortDlg->getSerialPort();
    QString str = serial->getSerialName();

    if(serial->isOpened()) {
        ELoad_ConfigFile::bulid()->setSerialName(str);
        str += tr(" 已打开");
        pe.setColor(QPalette::WindowText,Qt::black);
    } else {
        str += tr(" 串口未打开");
        pe.setColor(QPalette::WindowText,Qt::red);
    }

    ui->serialLab->setText(str);
    ui->serialLab->setPalette(pe);
}

void ELoad_SettingToolWid::on_serialBtn_clicked()
{
    mSerialPortDlg->exec();
    updateSerialWid();
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


/**
 * @brief 更新设备数量
 * @param num
 */
void ELoad_SettingToolWid::updateDevNum(int num)
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    config->item->devNum = num;
    config->setDevNum(num);
}

void ELoad_SettingToolWid::initDevNum()
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    int num = config->getDevNum();;
    updateDevNum(num);
    ui->spinBox->setValue(num);
}


void ELoad_SettingToolWid::on_devNumBtn_clicked()
{
    updateDevNum(ui->spinBox->value());
}
