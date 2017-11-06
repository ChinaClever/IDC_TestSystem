#include "serialportwid.h"
#include "ui_serialportwid.h"

SerialPortWid::SerialPortWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPortWid)
{
    ui->setupUi(this);

    initSerialPort();
    initWidget();
}

SerialPortWid::~SerialPortWid()
{
    delete ui;
}


void SerialPortWid::initSerialPort()
{
    mSerialPort = new SerialPort(this);

    QStringList com = mSerialPort->getList(); // 端口列表
    ui->comBox->clear();
    ui->comBox->addItems(com);

    QString name = mSerialPort->getSerialName(); // 已打开端口
    if(!name.isEmpty())
        ui->comBox->setCurrentText(name);
}


void SerialPortWid::initWidget()
{
    connect(ui->comBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(serialPortChanged(QString)));
    connect(ui->workBtn,SIGNAL(clicked()),this,SLOT(workBtnSlot()));
    connect(ui->updateBtn,SIGNAL(clicked()),this,SLOT(updateBtnSlot()));
}



/**
 * @brief 选择不同串口号时重新打开
 * @param com
 */
void SerialPortWid::serialPortChanged(QString com)
{
    if(!com.isEmpty())
    {
        mSerialPort->close();
        bool ret = mSerialPort->open(com);
        if(ret) {
            ui->workBtn->setText(tr("关闭串口"));
            ui->stateLab->setText(tr("串口已打开"));
        }  else {
            ui->workBtn->setText(tr("打开串口"));
            ui->stateLab->setText(tr("串口打开失败"));
            CriticalMsgBox box(this, tr("打开串口%1失败").arg(com));
        }
    }
}



void SerialPortWid::openSerialSlot()
{
    if(mSerialPort->isOpened()) /*已打开，现在是关闭窗口*/
    {
        mSerialPort->close();
        ui->workBtn->setText(tr("打开串口"));
        ui->stateLab->setText(tr("串口已关闭"));
    } else { /*未打开，现在打开*/
        QString com = ui->comBox->currentText();
        if(!com.isEmpty())
            serialPortChanged(com);
        else
             CriticalMsgBox box(this, tr("没有串口"));
    }
}


void SerialPortWid::workBtnSlot()
{
    openSerialSlot();
}


void SerialPortWid::updateBtnSlot()
{
    disconnect(ui->comBox,SIGNAL(currentIndexChanged(QString)), this,SLOT(serialPortChanged(QString)));  //断开信号

    initSerialPort();
    connect(ui->comBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(serialPortChanged(QString)));
}
