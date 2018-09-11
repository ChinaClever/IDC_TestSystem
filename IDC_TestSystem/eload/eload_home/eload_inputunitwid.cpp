/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_inputunitwid.h"
#include "ui_eload_inputunitwid.h"

ELoad_InputUnitWid::ELoad_InputUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_InputUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    QTimer::singleShot(1500,this,SLOT(initFunSLot())); //延时初始化
}

ELoad_InputUnitWid::~ELoad_InputUnitWid()
{
    delete ui;
}


void ELoad_InputUnitWid::initFunSLot()
{
    mRtu = ELoad_RtuSent::bulid();

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

void ELoad_InputUnitWid::init(int addr, int bit)
{
    mObjData = &(IN_DataPackets::bulid()->getDev(addr)->data.input[bit]);
    QString str = QString::number((addr-1) * 8 + bit+1);
    ui->inputLab->setText(str);
    mAddr = addr;
    mBit = bit;
}

void ELoad_InputUnitWid::updateWid()
{
    if(mObjData->cur.value) {
        double value = mObjData->cur.value / COM_RATE_CUR;
        QString str = QString::number(value) + " A";
        ui->curLab->setText(str);

        QPalette pe;
        if(mObjData->cur.alarm) {
            pe.setColor(QPalette::WindowText,Qt::red);
        } else {
            pe.setColor(QPalette::WindowText,Qt::black);
        }
        ui->curLab->setPalette(pe);

        str = tr("断开");
        if(mObjData->sw == 1) {
            str = tr("接通");
            pe.setColor(QPalette::WindowText,Qt::black);
        } else {
            pe.setColor(QPalette::WindowText,Qt::red);
        }
        ui->swLab->setText(str);
        ui->swLab->setPalette(pe);
    }
}

void ELoad_InputUnitWid::timeoutDone()
{
    updateWid();
}

void ELoad_InputUnitWid::on_openBtn_clicked()
{
    mRtu->switchOpenCtr(mAddr, mBit);
}

void ELoad_InputUnitWid::on_closeBtn_clicked()
{
    mRtu->switchCloseCtr(mAddr, mBit);
}

void ELoad_InputUnitWid::on_checkBox_clicked(bool checked)
{
    ui->horizontalScrollBar->setEnabled(!checked);
    if(checked) {
        mRtu->setDpAdjust(mAddr, ELoad_DP_1+mBit, 0 , 1000, 10);
    } else {
        mRtu->setData(mAddr, ELoad_DP_1+mBit, 0);
    }
}

void ELoad_InputUnitWid::on_horizontalScrollBar_valueChanged(int value)
{
    mRtu->setData(mAddr, ELoad_DP_1+mBit, value);
}
