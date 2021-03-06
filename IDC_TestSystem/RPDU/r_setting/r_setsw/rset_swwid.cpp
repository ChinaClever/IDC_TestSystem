﻿#include "rset_swwid.h"
#include "ui_rset_swwid.h"

RSet_SwWid::RSet_SwWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_SwWid)
{
    ui->setupUi(this);
    mReg = R_RtuReg_OutputSw;
    initwid();
}

RSet_SwWid::~RSet_SwWid()
{
    delete ui;
}

void RSet_SwWid::initwid()
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new RSet_SwItemWid(wid[i]);
        mWid[i]->init(i);
    }


    mSnmp = new RSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new RSet_RtuThread(this);
    mRtu->mReg = mReg;
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}

void RSet_SwWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void RSet_SwWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
}

void RSet_SwWid::sendRtu(int i)
{
    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + i;
    cmd.value = mWid[i]->status();
    mRtu->setCmd(cmd);
}

void RSet_SwWid::sendSnmp(int i)
{
    sSnmpSetCmd cmd;
    int addr = ui->spinBox->value();
    QString oid = QString("%1.%2.%3.1.9.%4.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+1);
    cmd.oid = oid;
    cmd.type = SNMP_STRING_TYPE;
    cmd.value.append( mWid[i]->status()==1 ? "ON":"OFF");
    mSnmp->setCmd(cmd);
}

void RSet_SwWid::on_pushButton_clicked()
{
    sConfigItem *item = R_ConfigFile::bulid()->item;
    for(int i=0; i<24; ++i) {
        if(mWid[i]->select()) {
            if(item->setMode == Test_SNMP) {
                sendSnmp(i);  // 增加SNMP命令
            } else {
                sendRtu(i);
            }
        }
    }

    mSnmp->start();
    mRtu->start();

    ui->textEdit->clear();
}

void RSet_SwWid::on_openRadio_clicked(bool checked)
{
    ui->closeRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setOpen(checked);
    }
}

void RSet_SwWid::on_closeRadio_clicked(bool checked)
{
    ui->openRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setClose(checked);
    }
}
