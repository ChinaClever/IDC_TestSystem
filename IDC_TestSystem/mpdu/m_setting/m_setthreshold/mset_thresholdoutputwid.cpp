﻿/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_thresholdoutputwid.h"
#include "ui_mset_thresholdoutputwid.h"

MSet_ThresholdOutputWid::MSet_ThresholdOutputWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_ThresholdOutputWid)
{
    ui->setupUi(this);    
    //mReg = 157;

    mReg = ZM_RtuReg_OutputCurMin;
}

MSet_ThresholdOutputWid::~MSet_ThresholdOutputWid()
{
    delete ui;
}


//int MSet_ThresholdOutputWid::getReg(int mode)//旧的MTU协议
//{
//    int reg=1054;

//    switch (mode) {
//    case Mpdu_Rtu_Test_min: reg = 1099; break;
//    case Mpdu_Rtu_Test_crMin: reg = 1123; break;
//    case Mpdu_Rtu_Test_crMax: reg = 1147; break;
//    case Mpdu_Rtu_Test_max: reg = 1181; break;
//    case Mpdu_Rtu_Test_delay: reg = 1055; break;
//    default: break;
//    }

//    return reg;
//}
int MSet_ThresholdOutputWid::getReg(int mode)
{
    int reg=ZM_RtuReg_OutputCurMin;

    switch (mode) {
    case Mpdu_Rtu_Test_min: reg = ZM_RtuReg_OutputCurMin; break;
    case Mpdu_Rtu_Test_crMin: reg = ZM_RtuReg_OutputCurCrMin; break;
    case Mpdu_Rtu_Test_crMax: reg = ZM_RtuReg_OutputCurCrMax; break;
    case Mpdu_Rtu_Test_max: reg = ZM_RtuReg_OutputCurMax; break;
    default: break;
    }

    return reg;
}

QString MSet_ThresholdOutputWid::getOid(int mode)
{
    int addr = ui->spinBox->value() , index = 2;
    QString oid = QString("%1.%2.%3.8").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr);

    switch (mode) {
    case Mpdu_Rtu_Test_min: oid += QString(".%1").arg(index); break;
    case Mpdu_Rtu_Test_crMin: oid += QString(".%1").arg(index + 1); break;
    case Mpdu_Rtu_Test_crMax: oid += QString(".%1").arg(index + 2); break;
    case Mpdu_Rtu_Test_max: oid += QString(".%1").arg(index + 3); break;
    default: oid += QString(".%1").arg(index);break;
    }

    return oid;
}

void MSet_ThresholdOutputWid::initwid(int mode)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new MSet_ThresholdItemWid(wid[i]);
        mWid[i]->initOutput(i, mode);
    }

    mOid = getOid(mode);
    mSnmp = new MSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mReg = getReg(mode);
    mRtu = new MSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
    mRtu->mReg = mReg;
}

void MSet_ThresholdOutputWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MSet_ThresholdOutputWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
    on_curSpinBox_valueChanged(ui->curSpinBox->value());
}

void MSet_ThresholdOutputWid::sendRtu(int i)
{
    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + i;
    cmd.value = mWid[i]->status();
    mRtu->setCmd(cmd);
}

void MSet_ThresholdOutputWid::sendSnmp(int i)
{
    sSnmpSetCmd cmd;
    cmd.oid = mOid + QString(".%1.0").arg(i+1);
    cmd.type = SNMP_STRING_TYPE;
    cmd.value.append( QString("%1.0").arg(mWid[i]->status()));
    mSnmp->setCmd(cmd);
}
void MSet_ThresholdOutputWid::on_pushButton_clicked()
{
    sConfigItem *item = M_ConfigFile::bulid()->item;
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


void MSet_ThresholdOutputWid::on_curSpinBox_valueChanged(int arg1)
{
    if(ui->checkBox->isChecked())
    {
        for(int i=0; i<24; ++i)
            mWid[i]->setValue(arg1);
    }
}

