#include "modetoolwid.h"
#include "ui_modetoolwid.h"

ModeToolWid::ModeToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeToolWid)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    mSerialPortDlg = new SerialPortDlg(this);

    QTimer::singleShot(400,this,SLOT(initFunSLot())); //延时初始化
    on_comboBox_currentIndexChanged(0);
}

ModeToolWid::~ModeToolWid()
{
    delete ui;
}

void ModeToolWid::initFunSLot()
{
    initSerialPort();

    QString ip = mConfig->getIp();
    if(!ip.isEmpty())  ui->lineEdit->setText(ip);
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
            //            ret = serial->open(com);
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



/**
 * @brief 开始模拟测试
 */
void ModeToolWid::startTest()
{
    int mode = Test_SNMP;
    int index = ui->comboBox->currentIndex();
    if(index) mode = Test_Rtu;

    mConfig->item->testMode = mode;
    mConfig->item->setMode = mode;
    QString ip = ui->lineEdit->text();
    mConfig->item->ip = ip;
    mConfig->setIp(ip);
    emit simulateSig(mode);

    ui->comboBox->setEnabled(false);
    ui->lineEdit->setEnabled(false);
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
        ui->lineEdit->setEnabled(true);
    }

    return ret;
}




void ModeToolWid::on_testBtn_clicked()
{
    int mode = mConfig->item->testMode;
    if(mode == Test_Stop) {
        startTest();
    } else {
        stopTest();
    }
}


void ModeToolWid::on_comboBox_currentIndexChanged(int index)
{
    bool en = true;
    if(index)  en = false;
    ui->serialBtn->setHidden(en);
    ui->serialLab->setHidden(en);

    ui->lineEdit->setHidden(!en);
}

