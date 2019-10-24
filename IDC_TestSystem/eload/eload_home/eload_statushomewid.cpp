/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_statushomewid.h"
#include "ui_eload_statushomewid.h"
#include "eload_com/in_datapackets.h"
#include "eload_rtu/eload_rtusent.h"
#include "eload_rtu/in_rtuthread.h"
extern void Delay_MSec(unsigned int msec);
ELoad_StatusHomeWid::ELoad_StatusHomeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_StatusHomeWid)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    mSec = 0;
    isRun = false;
    ui->resistanceLineEdit->setValidator(new QIntValidator(40, 20000, this));
    ui->modeBox->setCurrentIndex(2);
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    ui->eleBtn->setStyleSheet("QPushButton{background-color:rgb(219,241,252);color:rgb(0,0,0);}"
                              "QPushButton:hover{background-color:rgb(219,241,252);color:rgb(0,0,0);}"
                              "QPushButton:pressed{background-color:rgb(219,241,252);color:rgb(0,0,0);}");
}

ELoad_StatusHomeWid::~ELoad_StatusHomeWid()
{
    delete ui;
}

void ELoad_StatusHomeWid::updateTotalShowWid()
{
    int mode = 1;
    IN_DataPackets *packets = IN_DataPackets::bulid();

    double value = packets->getTgValue(mode++) / COM_RATE_VOL;
    QString str = QString::number(value) + " V";
    ui->volLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_CUR2;
    str = QString::number(value) + " A";
    ui->curLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_POW;
    str = QString::number(value) + " kW";
    ui->powLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_ELE;
    str = QString::number(value) + " kWh";
    ui->eleLab->setText(str);

    value = packets->getTgValue(mode++);
    str = QString::number(value) + " HZ";
    ui->hzLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_TEM;
    str = QString::number(value) + " ℃";
    ui->temLab->setText(str);
    ui->groupBox_2->setTitle(tr("总状态显示区"));

    for(int i = 1 ; i <= 3 ; i++)
        updateIndexShowWid(i);
}

void ELoad_StatusHomeWid::updateIndexShowWid(int index)
{
    int mode = 1;
    QString qstr("");
    QString spacestr="  ";
    IN_DataPackets *packets = IN_DataPackets::bulid();

    double value = packets->getTgValueByIndex(mode++,index) / COM_RATE_VOL;
    QString str = QString::number(value) + " V";

    value = packets->getTgValueByIndex(mode++,index) / COM_RATE_CUR2;
    str = QString::number(value) + " A";
    qstr = "                 "+tr("总电流：")+ str;

    value = packets->getTgValueByIndex(mode++,index) / COM_RATE_POW;
    str = QString::number(value) + " KW";
    qstr += spacestr+tr("有功功率：")+ str;

    value = packets->getTgValueByIndex(mode++,index) / COM_RATE_ELE;
    str = QString::number(value) + " KWh";
    qstr += spacestr+tr("总电能：")+ str;

    value = packets->getTgValueByIndex(mode++,index);
    str = QString::number(value) + " HZ";

    value = packets->getTgValueByIndex(mode++,index) / COM_RATE_TEM;
    str = QString::number(value) + " ℃";
    qstr += spacestr+tr("机箱温度：")+ str;
    emit updateIndexSig(index,qstr);
}

void ELoad_StatusHomeWid::updateWid()
{
    updateTotalShowWid();
}

bool ELoad_StatusHomeWid::checkRunTime()
{
    bool ret = ui->timeCheckBox->isChecked();
    if(!ret)
    {
        int sec = ui->timeSpinBox->value() * 60;
        if(sec > mSec) ret = true;
    }

    return ret;
}

void ELoad_StatusHomeWid::updateRunTime()
{
    QString str = "---";
    if(isRun) {
        bool ret = checkRunTime();
        if(ret) {
            int min = mSec++ / 60 ;
            int hour = min / 60;
            int day = hour / 24;
            str = tr("%1天 %2时 %3分 %4秒").arg(day).arg(hour%24).arg(min%60).arg(mSec%60);
        } else {
            on_startBtn_clicked();
        }
    }
    ui->timeLab->setText(str);
}

void ELoad_StatusHomeWid::timeoutDone()
{
    updateWid();
    updateRunTime();
}

void ELoad_StatusHomeWid::openInput()
{
    int start = ui->inputStartSpinBox->value();
    int end = ui->inputEndSpinBox->value();

    if(ui->inputCheckBox->isChecked()) {
        on_openBtn_clicked();
    } else {
        for(int i=start; i<=end; ++i) {
            int addr = i / 8 +1; int bit = i % 8;
            ELoad_RtuSent::bulid()->switchOpenCtr(addr, bit);
        }
    }
}

void ELoad_StatusHomeWid::setMode()
{
    int mode = ui->modeBox->currentIndex();
    switch(mode) {
    case 0: // 全部自动调整模块
        ELoad_RtuSent::bulid()->setAllDpAdjust();
        break;
    case 1: // 大电流模式
    {
        int start = ui->inputStartSpinBox->value();
        int end = ui->inputEndSpinBox->value();
        if( ui->startBtn->text() == tr("启动") ){
            for(int i = start ; i <= end ; i++ )
            {
                ELoad_RtuSent::bulid()->setBigCur(i,1);//打开大电流模式
                Delay_MSec(1000);
            }
        }
        break;
    }
    case 2: // 手动模式

        break;
    case 3: // 多个手动静态模式
    {
        int start = ui->inputStartSpinBox->value();
        int end = ui->inputEndSpinBox->value();
        int value = ui->resistanceLineEdit->text().toInt();
        if(ELoad_RtuSent::bulid()->mSerial->mSerial->isOpened()){
            if(value<40 || value>20000){
                InfoMsgBox box(this, tr("阻值不在范围！！"));
                return;
            }else{
                InfoMsgBox box(this, tr("设置成功！！"));
                emit sendResistanceCmdSig(start,end,value);
                /////////循环发送起始输出位和结束输出位，阻值命令函数
            }
        }
        else {
                InfoMsgBox box(this, tr("注意串口是否打开！！"));
        }
    }
        break;
    default:

        break;
    }
}

int ELoad_StatusHomeWid::getMode()
{
    return ui->modeBox->currentIndex();
}

void ELoad_StatusHomeWid::startUp()
{
    int start = ui->inputStartSpinBox->value();
    int end = ui->inputEndSpinBox->value();
    if(start > end){
        InfoMsgBox box(this, tr("起始位不能小于结束位！！"));
        return;
    }
    mSec = 0;
    //openInput();
    setMode();
    int ret = getMode();
    if(ret != 3)
    {
        isRun = true;
        ui->groupBox->setEnabled(false);
        ui->startBtn->setText(tr("停止"));
        ELoad_ConfigFile::bulid()->item->testMode = ELoad_Test_Simulate;
    }
}

void ELoad_StatusHomeWid::stopFun()
{
    isRun = false;

    if(ui->modeBox->currentIndex() == 1 && ui->startBtn->text() == tr("停止") ){
        int start = ui->inputStartSpinBox->value();
        int end = ui->inputEndSpinBox->value();
        for(int i = start ; i <= end ; i++ ){
            ELoad_RtuSent::bulid()->setBigCur(i,0);//关闭大电流模式
            Delay_MSec(1000);
        }
    }
    ui->groupBox->setEnabled(true);
    ui->startBtn->setText(tr("启动"));
    ELoad_ConfigFile::bulid()->item->testMode = ELoad_Test_Stop;
}

void ELoad_StatusHomeWid::on_startBtn_clicked()
{
    //on_closeBtn_clicked();
    if(isRun) {
        stopFun();
    } else {
        startUp();
    }
}

void ELoad_StatusHomeWid::on_openBtn_clicked()
{
    ELoad_RtuSent::bulid()->switchOpenAll();
}

void ELoad_StatusHomeWid::on_closeBtn_clicked()
{
    ELoad_RtuSent::bulid()->switchCloseAll();
}

void ELoad_StatusHomeWid::on_eleBtn_clicked()
{
    sRtuSentCom cmd;
    cmd.addr = 0xff;

    cmd.fn = 0x10;
    cmd.reg = 0x1039;
    cmd.len = 0;
    IN_RtuThread::bulid()->sentCmd(cmd);
}

void ELoad_StatusHomeWid::on_modeBox_currentIndexChanged(int index)
{
    switch(index) {
    case 0: // 全部自动调整模块
    {
        ui->startBtn->setText(tr("启动"));
        ui->label_5->setText(tr("输出位"));
        show();
    }
        break;
    case 1: // 大电流模式
    {
        ui->startBtn->setText(tr("启动"));
        ui->label_5->setText(tr("地址"));
        show();
    }
        break;
    case 2: // 手动模式
    {
        ui->startBtn->setText(tr("启动"));
        hide();
    }
        break;
    case 3: // 多个手动静态模式
    {
        ui->startBtn->setText(tr("设置"));
        ui->label_5->setText(tr("输出位"));
        show();
    }
        break;
    default:
        break;
    }
}

void ELoad_StatusHomeWid::show()
{
    ui->resistanceLineEdit->show();
    ui->inputStartSpinBox->show();
    ui->inputEndSpinBox->show();
    ui->inputLab->show();
    ui->inputCheckBox->show();
    ui->lab_3->show();
    ui->label_5->show();
}
void ELoad_StatusHomeWid::hide()
{
    ui->resistanceLineEdit->hide();
    ui->inputStartSpinBox->hide();
    ui->inputEndSpinBox->hide();
    ui->inputLab->hide();
    ui->inputCheckBox->hide();
    ui->lab_3->hide();
    ui->label_5->hide();
}
