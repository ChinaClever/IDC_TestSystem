﻿#include "zset_outputelewid.h"
#include "ui_zset_outputelewid.h"

ZSet_OutputEleWid::ZSet_OutputEleWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_OutputEleWid)
{
    ui->setupUi(this);
    mReg = Z_RtuReg_OutputEle;
    initwid();
}

ZSet_OutputEleWid::~ZSet_OutputEleWid()
{
    delete ui;
}
void ZSet_OutputEleWid::initwid()
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new ZSet_EleItemWid(wid[i]);
        mWid[i]->init(i);
    }

    mSnmp = new ZSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new ZSet_RtuThread(this);
    mRtu->mReg = mReg;
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void ZSet_OutputEleWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void ZSet_OutputEleWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
}
void ZSet_OutputEleWid::sendSnmp(int i)
{
    if(mWid[i]->status())
    {
        sSnmpSetCmd cmd;
        int addr = ui->spinBox->value();
        QString oid = QString("%1.%2.%3.10.%4.0").arg(MIB_OID_CLEVER).arg(Z_MIB_OID).arg(addr).arg(i+1);
        cmd.oid = oid;
        cmd.type = SNMP_STRING_TYPE;

        cmd.value.append("0.0");
        //qDebug()<< cmd.oid  << cmd.value;
        mSnmp->setCmd(cmd);
    }
}

void ZSet_OutputEleWid::sendRtu(int i)
{
    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + i;
    cmd.value = mWid[i]->status();
    mRtu->setCmd(cmd);
}

void ZSet_OutputEleWid::on_pushButton_clicked()
{
    sConfigItem *item = Z_ConfigFile::bulid()->item;

    for(int i=0; i<24; ++i) {
        if(mWid[i]->select()) {
            if(item->setMode == Test_SNMP)
            {
                sendSnmp(i);
            }
            else
            {
                sendRtu(i);
            }
        }
    }

    mSnmp->start();
    mRtu->start();
    ui->textEdit->clear();
}
void ZSet_OutputEleWid::on_cleanRadio_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setClean(checked);
    }
}
