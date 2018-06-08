#include "bus_settingtoolwid.h"
#include "ui_bus_settingtoolwid.h"


BUS_SettingToolWid::BUS_SettingToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_SettingToolWid)
{
    ui->setupUi(this);
    mSerialPortDlg = new SerialPortDlg(this);

    initSerialPort();
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
            ret = serial->open(com);
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
    QString str = serial->getSerialName();

    if(serial->isOpened()) {
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
