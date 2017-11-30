#include "sisettingtoolwid.h"
#include "ui_sisettingtoolwid.h"
#include "si_com/siconfigfile.h"
#include "sisetlinenum.h"
#include "sisetdevnumdlg.h"
#include "sisetmodbuscmddlg.h"
#include "sisetmodbustimedlg.h"

SiSettingToolWid::SiSettingToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiSettingToolWid)
{
    ui->setupUi(this);

    mSerialPortDlg = new SerialPortDlg(this);
    initSerialPort();
    initLineNum();
    initDevNum();
    initDevCmd();
    initModbusTime();
}

SiSettingToolWid::~SiSettingToolWid()
{
    delete ui;
}

bool SiSettingToolWid::initSerialPort()
{
    bool ret = false;

    SiConfigFile *config = SiConfigFile::bulid();
    QString com = config->getSerialName();
    if(!com.isEmpty())
    {
        SerialPort *serial = mSerialPortDlg->getSerialPort();
        config->item->serial = serial;
        ret = serial->isContains(com);
        if(ret) {
            ret = serial->open(com);
            updateSerialWid();
        }
    }

    return ret;
}

void SiSettingToolWid::updateSerialWid()
{
    QPalette pe;
    SerialPort *serial = mSerialPortDlg->getSerialPort();
    QString str = serial->getSerialName();

    if(serial->isOpened()) {
        SiConfigFile::bulid()->setSerialName(str);
        str += tr(" 已打开");
        pe.setColor(QPalette::WindowText,Qt::black);
    } else {
        str += tr(" 串口未打开");
        pe.setColor(QPalette::WindowText,Qt::red);
    }

    ui->serialLab->setText(str);
    ui->serialLab->setPalette(pe);
}

void SiSettingToolWid::on_serialBtn_clicked()
{
    mSerialPortDlg->exec();
    updateSerialWid();
}

void SiSettingToolWid::updateLineNum(int num)
{
    SiConfigFile *config = SiConfigFile::bulid();
    config->item->lineNum = num;

    QString str;
    switch (num) {
    case 1:  str = tr("单相"); break;
    case 2:  str = tr("二相"); break;
    case 3:  str = tr("三相"); break;
    default:
        break;
    }
    ui->devLineLab->setText(str);
    config->setLineNum(num);
}

void SiSettingToolWid::initLineNum()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->getLineNum();;
    updateLineNum(num);
}

void SiSettingToolWid::on_lineBtn_clicked()
{
    SiSetLineNum dlg(this);
    if(dlg.exec() == QDialog::Accepted)
        updateLineNum(dlg.getLineNum());
}

void SiSettingToolWid::updateDevNum(int num)
{
    SiConfigFile *config = SiConfigFile::bulid();
    config->item->devNum = num;

    QString str = QString::number(num);
    ui->devNumLab->setText(str);
    config->setDevNum(num);
}

void SiSettingToolWid::initDevNum()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->getDevNum();;
    updateDevNum(num);
}

void SiSettingToolWid::on_devNumBtn_clicked()
{
    SiSetDevNumDlg dlg(this);
    if(dlg.exec() == QDialog::Accepted)
        updateDevNum(dlg.getNum());
}

void SiSettingToolWid::updateDevCmd(int num)
{
    SiConfigFile *config = SiConfigFile::bulid();
    config->item->cmdModel = num;

    QString str;
    switch (num) {
    case 1:  str = tr("单命令"); break;
    case 2:  str = tr("双命令"); break;
    default:
        break;
    }

    ui->devCmdLab->setText(str);
    config->setModbusCmd(num);
}

void SiSettingToolWid::initDevCmd()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->getModbusCmd();
    updateDevCmd(num);
}

void SiSettingToolWid::on_cmdBtn_clicked()
{
    SiSetModbusCmdDlg dlg(this);
    if(dlg.exec() == QDialog::Accepted)
        updateDevCmd(dlg.getCmdNum());
}

void SiSettingToolWid::updateModbusTime(int num)
{
    SiConfigFile *config = SiConfigFile::bulid();
    config->item->msecs = 5*(num+1);

    QString str = QString::number(config->item->msecs) + "00ms";
    ui->timeLab->setText(str);
    config->setModbusTime(num);
}

void SiSettingToolWid::initModbusTime()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->getModbusTime();
    updateDevCmd(num);
}

void SiSettingToolWid::on_timeBtn_clicked()
{
    SiSetModbusTimeDlg dlg(this);
    if(dlg.exec() == QDialog::Accepted)
        updateModbusTime(dlg.getIndex());
}
