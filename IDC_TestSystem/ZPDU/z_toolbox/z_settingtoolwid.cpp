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
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    mSerialPortDlg = new SerialPortDlg(this);

    initSerialPort();
    initModbusTime();
    initDevCmd();
    initDevNum();
}

Z_SettingToolWid::~Z_SettingToolWid()
{
    delete ui;
}

/**
 * @brief 初始化串口
 * @return
 */
bool Z_SettingToolWid::initSerialPort()
{
    bool ret = false;

    Z_ConfigFile *config = Z_ConfigFile::bulid();
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
void Z_SettingToolWid::updateSerialWid()
{
    QPalette pe;
    SerialPort *serial = mSerialPortDlg->getSerialPort();
    QString str = serial->getSerialName();

    if(serial->isOpened()) {
        Z_ConfigFile::bulid()->setSerialName(str);
        str += tr(" 已打开");
        pe.setColor(QPalette::WindowText,Qt::black);
    } else {
        str += tr(" 串口未打开");
        pe.setColor(QPalette::WindowText,Qt::red);
    }

    ui->serialLab->setText(str);
    ui->serialLab->setPalette(pe);
}

void Z_SettingToolWid::on_serialBtn_clicked()
{
    mSerialPortDlg->exec();
    updateSerialWid();
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

