/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_settingtoolwid.h"
#include "ui_bus_settingtoolwid.h"


BUS_SettingToolWid::BUS_SettingToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_SettingToolWid)
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

BUS_SettingToolWid::~BUS_SettingToolWid()
{
    delete ui;
}


/**
 * @brief 初始化串口
 * @return
 */
bool BUS_SettingToolWid::initSerialPort()
{
    bool ret = false;

    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
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
void BUS_SettingToolWid::updateSerialWid()
{
    QPalette pe;
    SerialPort *serial = mSerialPortDlg->getSerialPort();
    QString str;

    if(serial->isOpened()) {
        str = serial->getSerialName();
        BUS_ConfigFile::bulid()->setSerialName(str);
        str += tr(" 已打开");
        pe.setColor(QPalette::WindowText,Qt::black);
    } else {
        str += tr(" 串口未打开");
        pe.setColor(QPalette::WindowText,Qt::red);
    }

    ui->serialLab->setText(str);
    ui->serialLab->setPalette(pe);
}

void BUS_SettingToolWid::on_serialBtn_clicked()
{
    mSerialPortDlg->exec();
    updateSerialWid();
}


/**
 * @brief 更新
 * @param num
 */
void BUS_SettingToolWid::updateDevCmd(int num)
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    config->item->cmdModel = num;
    config->setModbusCmd(num);
}

void BUS_SettingToolWid::initDevCmd()
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    int num = config->getModbusCmd();
    updateDevCmd(num);

    ui->cmdBox->setCurrentIndex(num-1);
}

void BUS_SettingToolWid::on_cmdBtn_clicked()
{
    int num = ui->cmdBox->currentIndex();
    updateDevCmd(num+1);
}



/**
 * @brief 更新间隔时间
 * @param num
 */
void BUS_SettingToolWid::updateModbusTime(int num)
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    config->item->msecs = 5*(num+1);
    config->setModbusTime(num);
}

void BUS_SettingToolWid::initModbusTime()
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    int num = config->getModbusTime();
    updateModbusTime(num);
    ui->timeBox->setCurrentIndex(num);
}

void BUS_SettingToolWid::on_timeBtn_clicked()
{
    updateModbusTime(ui->timeBox->currentIndex());
}


/**
 * @brief 更新设备数量
 * @param num
 */
void BUS_SettingToolWid::updateDevNum(int num)
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    config->item->devNum = num;
    config->setDevNum(num);
}

void BUS_SettingToolWid::initDevNum()
{
    BUS_ConfigFile *config = BUS_ConfigFile::bulid();
    int num = config->getDevNum();;
    updateDevNum(num);
    ui->spinBox->setValue(num);
}

void BUS_SettingToolWid::on_devNumBtn_clicked()
{
    updateDevNum(ui->spinBox->value());
}
