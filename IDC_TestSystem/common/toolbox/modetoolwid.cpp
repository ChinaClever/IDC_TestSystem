#include "modetoolwid.h"
#include "ui_modetoolwid.h"
#include "common.h"
#include <QGridLayout>

ModeToolWid::ModeToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeToolWid)
{
    ui->setupUi(this);

    mSerialPortDlg = new SerialPortDlg(this);

    mConfig = nullptr;
    QTimer::singleShot(300,this,SLOT(initFunSLot())); //延时初始化
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

ModeToolWid::~ModeToolWid()
{
    delete ui;
}

void ModeToolWid::initFunSLot()
{
    if(!mConfig){QTimer::singleShot(100,this,SLOT(initFunSLot()));  return ;}//延时初始化
    initSerialPort();
    initDevNum();

    QString ip = mConfig->getIp();
    if(ip.isEmpty()) ip = "192.168.1.163";
    ui->ipLineEdit->setText(ip);
    mConfig->item->ip = ip;

    int mode = mConfig->getTestMode();
    ui->comboBox->setCurrentIndex(mode);
    on_comboBox_currentIndexChanged(mode);
}

void ModeToolWid::sipdu()
{
    on_comboBox_currentIndexChanged(1);
    ui->comboBox->setHidden(true);
}

/**
 * @brief 初始化串口
 * @return
 */
bool ModeToolWid::initSerialPort()
{
    bool ret = false;

    SerialPort *serial = mSerialPortDlg->getSerialPort();
    mConfig->item->serial = serial;

    QString com = mConfig->getSerialName();
    if(!com.isEmpty())
    {
        ret = serial->isContains(com);
        if(ret) {
            // ret = serial->open(com);
            updateSerialWid();
        }
    }

    return ret;
}



/**
 * @brief 更新串口窗口
 */
void ModeToolWid::updateSerialWid()
{
    QPalette pe;
    SerialPort *serial = mSerialPortDlg->getSerialPort();
    QString str = serial->getSerialName();

    if(serial->isOpened()) {
        mConfig->setSerialName(str);
        str += tr(" 已打开");
        pe.setColor(QPalette::WindowText,Qt::black);
    } else {
        str += tr(" 串口未打开");
        pe.setColor(QPalette::WindowText,Qt::red);
    }

    ui->serialLab->setText(str);
    ui->serialLab->setPalette(pe);
}

void ModeToolWid::on_serialBtn_clicked()
{
    mSerialPortDlg->exec();
    updateSerialWid();
}


void ModeToolWid::on_settingBtn_clicked()
{
    int mode = mConfig->item->testMode;
    if(mode != Test_Stop) {
        QuMsgBox box(this, tr("此操作会停止测试，是否进入单项测试？？"));
        if(box.Exec())
            on_testBtn_clicked();
        else
            return ;
    }
    emit simulateSig(Info_Set);
}


bool ModeToolWid::checkInput()
{
    bool ret = mConfig->item->serial->isOpened();
    if(!ret) {
        CriticalMsgBox box(this, tr("串口未打开，请先打开串口!!!"));
    } else {
        QString ip = ui->ipLineEdit->text();
        ret = cm_isIPaddress(ip);
        if(!ret) {
            CriticalMsgBox box(this, tr("IP地址输入有误，请重新输入!!!"));
        }
    }

    return ret;
}

/**
 * @brief 开始模拟测试
 */
void ModeToolWid::startTest()
{
    int mode = ui->comboBox->currentIndex() + 1;
    QString ip = ui->ipLineEdit->text();
    mConfig->item->ip = ip;
    mConfig->setIp(ip);

    mConfig->item->testMode = mode;
    mConfig->item->setMode = mode;
    emit simulateSig(mode);

    ui->comboBox->setEnabled(false);
    ui->ipLineEdit->setEnabled(false);
    ui->testBtn->setText(tr("停止测试"));
}

/**
 * @brief 停止模拟测试
 */
bool ModeToolWid::stopTest()
{
    bool ret = false;
    QuMsgBox box(this, tr("是否停止测试？？"));
    if(box.Exec()) {
        mConfig->item->testMode = Test_Stop;
        emit simulateSig(Test_Stop);

        ret = true;
        ui->testBtn->setText(tr("启动测试"));
        ui->comboBox->setEnabled(true);
        ui->ipLineEdit->setEnabled(true);
    }

    return ret;
}


void ModeToolWid::on_testBtn_clicked()
{
    int mode = mConfig->item->testMode;
    if(mode == Test_Stop) {
        if(ui->comboBox->currentIndex()==1&&checkInput())  startTest();
        else if(ui->comboBox->currentIndex()==0||ui->comboBox->currentIndex()==2)startTest();
    } else {
        stopTest();
    }
}

void ModeToolWid::on_comboBox_currentIndexChanged(int index)
{
    bool serialEn = true, ipEn = true;
    switch (index) {
    case 0: ipEn = false; break;
    case 1: serialEn = false; break;
    case 2: ipEn = false;serialEn = false; break;

    default:  break;
    }

    ui->serialBtn->setHidden(serialEn);
    ui->serialLab->setHidden(serialEn);
    ui->ipLineEdit->setHidden(ipEn);
    mConfig->setTestMode(index);
}



/**
 * @brief 更新设备数量
 * @param num
 */
void ModeToolWid::updateDevNum(int num)
{
    mConfig->item->devNum = num;
    mConfig->setDevNum(num);
}

void ModeToolWid::initDevNum()
{
    int num = mConfig->getDevNum();;
    updateDevNum(num);
    ui->spinBox->setValue(num);
}

void ModeToolWid::on_devNumBtn_clicked()
{
    updateDevNum(ui->spinBox->value());
}

