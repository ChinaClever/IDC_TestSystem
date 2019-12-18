/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1set_swwid.h"
#include "ui_mv1set_swwid.h"

MV1Set_SwWid::MV1Set_SwWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1Set_SwWid)
{
    ui->setupUi(this);
    //mReg = 1003;
    mReg = MV1_RtuReg_OutputSw;
    initwid();
}

MV1Set_SwWid::~MV1Set_SwWid()
{
    delete ui;
}

void MV1Set_SwWid::initwid()
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new MV1Set_SwItemWid(wid[i]);
        mWid[i]->init(i);
    }

    mSnmp = new MV1Set_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new MV1Set_RtuThread(this);
    mRtu->mReg = mReg;
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}

void MV1Set_SwWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MV1Set_SwWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
}

void MV1Set_SwWid::sendRtu(int i)
{
    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + i;
    cmd.value = mWid[i]->status();
    mRtu->setCmd(cmd);
}

void MV1Set_SwWid::sendSnmp(int i)
{
    sSnmpSetCmd cmd;
    int addr = ui->spinBox->value();
    switch(addr)
    {
    case 1:addr = 8;break;
    case 2:addr = 15;break;
    case 3:addr = 22;break;
    case 4:addr = 29;break;
    default: addr = 8;break;
    }
    QString oid = QString("%1.%2.%3.%4.0").arg(MIB_OID_CLEVER).arg(MV1_MIB_OID).arg(addr).arg(i+1);
    // QString oid = QString("%1.%2.%3.5.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);

    cmd.oid = oid;
    cmd.type = SNMP_STRING_TYPE;
    cmd.value.append( mWid[i]->status()==1 ? "ON":"OFF");
    //cmd.value.append( mWid[i]->status()==1 ? tr("OUTPUT%1").arg(i+1):tr("output%1").arg(i+1));
    mSnmp->setCmd(cmd);
}

void MV1Set_SwWid::on_pushButton_clicked()
{
    sConfigItem *item = MV1_ConfigFile::bulid()->item;
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

void MV1Set_SwWid::on_openRadio_clicked(bool checked)
{
    ui->closeRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setOpen(checked);
    }
}

void MV1Set_SwWid::on_closeRadio_clicked(bool checked)
{
    ui->openRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setClose(checked);
    }
}
