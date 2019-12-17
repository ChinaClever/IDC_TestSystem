/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1set_lineunitwid.h"
#include "ui_mv1set_lineunitwid.h"

MV1Set_LineUnitWid::MV1Set_LineUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1Set_LineUnitWid)
{
    ui->setupUi(this);
}

MV1Set_LineUnitWid::~MV1Set_LineUnitWid()
{
    delete ui;
}


void MV1Set_LineUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new MV1Set_LineItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}

void MV1Set_LineUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; j++) {
            MV1Set_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                sRtuSetCmd cmd;
                cmd.addr = addr;
                cmd.reg =  mWid[i]->mReg + j;
                cmd.value = item->status();
                list.append(cmd);
            }
        }
    }
}
void MV1Set_LineUnitWid::getCmdList(int index , int addr, QList<sSnmpSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; j++) {
            MV1Set_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                sSnmpSetCmd cmd;
//                cmd.oid  = QString("%1.%2.%3.2.%4.%5.0")
//                        .arg(MIB_OID_CLEVER)
//                        .arg(MV1_MIB_OID)
//                        .arg(addr)
//                        .arg(j+1)
//                        .arg(index);
                cmd.type = SNMP_STRING_TYPE;
                cmd.value.append(QString("%1.00").arg(item->status()));
                //qDebug()<<cmd.oid<<cmd.value;
                list.append(cmd);
            }
        }
    }
}
