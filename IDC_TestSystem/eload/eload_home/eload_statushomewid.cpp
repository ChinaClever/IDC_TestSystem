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

ELoad_StatusHomeWid::ELoad_StatusHomeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_StatusHomeWid)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    mSec = 0;
    isRun = false;
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:rgb(219,241,252);color:rgb(0,0,0);}"
                                    "QPushButton:hover{background-color:rgb(219,241,252);color:rgb(0,0,0);}"
                                    "QPushButton:pressed{background-color:rgb(219,241,252);color:rgb(0,0,0);}");
}

ELoad_StatusHomeWid::~ELoad_StatusHomeWid()
{
    delete ui;
}

void ELoad_StatusHomeWid::updateWid()
{
    int mode = 1;
    IN_DataPackets *packets = IN_DataPackets::bulid();

    double value = packets->getTgValue(mode++) / COM_RATE_VOL;
    QString str = QString::number(value) + " V";
    ui->volLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_CUR;
    str = QString::number(value) + " A";
    ui->curLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_POW;
    str = QString::number(value) + " KW";
    ui->powLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_ELE;
    str = QString::number(value) + " KWh";
    ui->eleLab->setText(str);

    value = packets->getTgValue(mode++);
    str = QString::number(value) + " HZ";
    ui->hzLab->setText(str);

    value = packets->getTgValue(mode++) / COM_RATE_TEM;
    str = QString::number(value) + " ℃";
    ui->temLab->setText(str);
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
            str = tr("%1天 %2时 %3分 %4抄").arg(day).arg(hour%24).arg(min%60).arg(mSec%60);
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
    case 0: // 自动调整模块
        //ELoad_RtuSent::bulid()->setSingleDpAdjust();
        break;
    case 1: // 自动调整模块
        ELoad_RtuSent::bulid()->setAllDpAdjust();
        break;
    case 2: // 大电流模式

        break;

    case 3: // 手动模式

        break;
    }
}

void ELoad_StatusHomeWid::startUp()
{
    mSec = 0;
    isRun = true;

    openInput();
    setMode();
    ui->groupBox->setEnabled(false);
    ui->startBtn->setText(tr("停止"));
    ELoad_ConfigFile::bulid()->item->testMode = ELoad_Test_Simulate;
}

void ELoad_StatusHomeWid::stopFun()
{
    isRun = false;

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

