/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_hometoolwid.h"
#include "ui_eload_hometoolwid.h"

ELoad_HomeToolWid::ELoad_HomeToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_HomeToolWid)
{
    ui->setupUi(this);
//    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
//    gridLayout->addWidget(this);

    mSerialPortDlg = new SerialPortDlg(this);
    initSerialPort();
    initDevNum();
}

ELoad_HomeToolWid::~ELoad_HomeToolWid()
{
    delete ui;
}

void ELoad_HomeToolWid::on_homeBtn_clicked()
{
    emit toolSig(ELoad_Info_Home);
}


/**
 * @brief 初始化串口
 * @return
 */
bool ELoad_HomeToolWid::initSerialPort()
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
void ELoad_HomeToolWid::updateSerialWid()
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

void ELoad_HomeToolWid::on_serialBtn_clicked()
{
    mSerialPortDlg->exec();
    updateSerialWid();
}


/**
 * @brief 更新设备数量
 * @param num
 */
void ELoad_HomeToolWid::updateDevNum(int num)
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    config->item->devNum = num;
    config->setDevNum(num);
}

void ELoad_HomeToolWid::initDevNum()
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    int num = config->getDevNum();;
    updateDevNum(num);
    ui->spinBox->setValue(num);
}


void ELoad_HomeToolWid::on_devNumBtn_clicked()
{
    updateDevNum(ui->spinBox->value());
}



void ELoad_HomeToolWid::on_temriseBtn_clicked()
{
    int i = ui->temSpinBox->value() - 1;
    emit toolSig(ELoad_Tem_RiseOne + i);
}
