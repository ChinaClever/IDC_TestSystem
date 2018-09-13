#include "z_modetoolwid.h"
#include "ui_z_modetoolwid.h"

Z_ModeToolWid::Z_ModeToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Z_ModeToolWid)
{
    ui->setupUi(this);
    mSerialPortDlg = new SerialPortDlg(this);

    initSerialPort();
    on_comboBox_currentIndexChanged(0);
}

Z_ModeToolWid::~Z_ModeToolWid()
{
    delete ui;
}


/**
 * @brief 初始化串口
 * @return
 */
bool Z_ModeToolWid::initSerialPort()
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
void Z_ModeToolWid::updateSerialWid()
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

void Z_ModeToolWid::on_serialBtn_clicked()
{
    mSerialPortDlg->exec();
    updateSerialWid();
}


void Z_ModeToolWid::on_settingBtn_clicked()
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    int mode = config->item->testMode;
    if(mode != Test_Stop) {
        QuMsgBox box(this, tr("此操作会停止测试，是否进入单项测试？？"));
        if(box.Exec())
            on_testBtn_clicked();
        else
            return ;
    }
    emit simulateSig(Info_Set);
}



/**
 * @brief 开始模拟测试
 */
void Z_ModeToolWid::startTest()
{
    int mode = Test_SNMP;
    int index = ui->comboBox->currentIndex();
    if(index) mode = Test_Rtu;

    sConfigItem *item = Z_ConfigFile::bulid()->item;
    item->testMode = mode;
    item->ip = ui->lineEdit->text();
    emit simulateSig(mode);

    ui->comboBox->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->testBtn->setText(tr("停止测试"));
}

/**
 * @brief 停止模拟测试
 */
bool Z_ModeToolWid::stopTest()
{
    bool ret = false;
    QuMsgBox box(this, tr("是否停止测试？？"));
    if(box.Exec()) {
        Z_ConfigFile *config = Z_ConfigFile::bulid();
        config->item->testMode = Test_Stop;
        emit simulateSig(Test_Stop);

        ret = true;
        ui->testBtn->setText(tr("启动测试"));
        ui->comboBox->setEnabled(true);
        ui->lineEdit->setEnabled(true);
    }

    return ret;
}




void Z_ModeToolWid::on_testBtn_clicked()
{
    Z_ConfigFile *config = Z_ConfigFile::bulid();
    int mode = config->item->testMode;
    if(mode == Test_Stop) {
        startTest();
    } else {
        stopTest();
    }
}


void Z_ModeToolWid::on_comboBox_currentIndexChanged(int index)
{
    bool en = true;
    if(index)  en = false;
     ui->serialBtn->setHidden(en);
     ui->serialLab->setHidden(en);

     ui->lineEdit->setHidden(!en);
}
