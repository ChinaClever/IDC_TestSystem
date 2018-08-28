/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_settingtoolwid.h"
#include "ui_m_settingtoolwid.h"

M_SettingToolWid::M_SettingToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::M_SettingToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    mSerialPortDlg = new SerialPortDlg(this);

    initSerialPort();
    initModbusTime();
    initDevCmd();
    initDevNum();
    initOutputNum();
}

M_SettingToolWid::~M_SettingToolWid()
{
    delete ui;
}

/**
 * @brief 初始化串口
 * @return
 */
bool M_SettingToolWid::initSerialPort()
{
    bool ret = false;

    M_ConfigFile *config = M_ConfigFile::bulid();
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
void M_SettingToolWid::updateSerialWid()
{
    QPalette pe;
    SerialPort *serial = mSerialPortDlg->getSerialPort();
    QString str = serial->getSerialName();

    if(serial->isOpened()) {
        M_ConfigFile::bulid()->setSerialName(str);
        str += tr(" 已打开");
        pe.setColor(QPalette::WindowText,Qt::black);
    } else {
        str += tr(" 串口未打开");
        pe.setColor(QPalette::WindowText,Qt::red);
    }

    ui->serialLab->setText(str);
    ui->serialLab->setPalette(pe);
}

void M_SettingToolWid::on_serialBtn_clicked()
{
    mSerialPortDlg->exec();
    updateSerialWid();
}


/**
 * @brief 更新
 * @param num
 */
void M_SettingToolWid::updateDevCmd(int num)
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    config->item->cmdModel = num;
    config->setModbusCmd(num);
}

void M_SettingToolWid::initDevCmd()
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    int num = config->getModbusCmd();
    updateDevCmd(num);

    ui->cmdBox->setCurrentIndex(num-1);
}

void M_SettingToolWid::on_cmdBtn_clicked()
{
    int num = ui->cmdBox->currentIndex();
    updateDevCmd(num+1);
}



/**
 * @brief 更新间隔时间
 * @param num
 */
void M_SettingToolWid::updateModbusTime(int num)
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    config->item->msecs = 5*(num+1);
    config->setModbusTime(num);
}

void M_SettingToolWid::initModbusTime()
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    int num = config->getModbusTime();
    updateModbusTime(num);
    ui->timeBox->setCurrentIndex(num);
}

void M_SettingToolWid::on_timeBtn_clicked()
{
    updateModbusTime(ui->timeBox->currentIndex());
}


/**
 * @brief 更新设备数量
 * @param num
 */
void M_SettingToolWid::updateDevNum(int num)
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    config->item->devNum = num;
    config->setDevNum(num);
}

void M_SettingToolWid::initDevNum()
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    int num = config->getDevNum();;
    updateDevNum(num);
    ui->spinBox->setValue(num);
}


void M_SettingToolWid::on_devNumBtn_clicked()
{
    updateDevNum(ui->spinBox->value());
}

void M_SettingToolWid::updateOutputNum(int num)
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    config->item->outputNum = num;
    config->setOutputNum(num);
}

void M_SettingToolWid::initOutputNum()
{
    M_ConfigFile *config = M_ConfigFile::bulid();
    int num = config->getOutputNum();;
    updateOutputNum(num);
    ui->outputSpinBox->setValue(num);
}

void M_SettingToolWid::on_outputNumBtn_clicked()
{
    updateOutputNum(ui->outputSpinBox->value());
}
