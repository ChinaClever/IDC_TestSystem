/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_swwid.h"
#include "ui_mset_swwid.h"

MSet_SwWid::MSet_SwWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_SwWid)
{
    ui->setupUi(this);
    mReg = 1003;
    initwid();
}

MSet_SwWid::~MSet_SwWid()
{
    delete ui;
}


void MSet_SwWid::initwid()
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new MSet_SwItemWid(wid[i]);
        mWid[i]->init(i);
    }

    mSnmp = new MSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new MSet_RtuThread(this);
    mRtu->mReg = mReg;
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}

void MSet_SwWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MSet_SwWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
}


void MSet_SwWid::sendRtu(int i)
{
    sMTestRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + i;
    cmd.value = mWid[i]->status();
    mRtu->setCmd(cmd);
}

void MSet_SwWid::sendSnmp(int i)
{
    sSnmpSetCmd cmd;
    int addr = ui->spinBox->value();
    QString oid = QString("%1.%2.%3.7.%4").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);

    cmd.oid = oid;
    cmd.type = SNMP_INTEGER_TYPE;
    cmd.value.append( (char) mWid[i]->status());
    mSnmp->setCmd(cmd);
}

void MSet_SwWid::on_pushButton_clicked()
{
    sConfigItem *item = M_ConfigFile::bulid()->item;
    for(int i=0; i<24; ++i) {
        if(mWid[i]->select()) {
            if(item->testMode == Test_SNMP) {
                sendSnmp(i);  // 增加SNMP命令
            } else {
                sendRtu(i);
            }
        }
    }

    mRtu->start();
    ui->textEdit->clear();
}

void MSet_SwWid::on_openRadio_clicked(bool checked)
{
    ui->closeRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setOpen(checked);
    }
}

void MSet_SwWid::on_closeRadio_clicked(bool checked)
{
    ui->openRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setClose(checked);
    }
}
