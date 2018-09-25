/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_lineunitwid.h"
#include "ui_mset_lineunitwid.h"

MSet_LineUnitWid::MSet_LineUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_LineUnitWid)
{
    ui->setupUi(this);
}

MSet_LineUnitWid::~MSet_LineUnitWid()
{
    delete ui;
}


void MSet_LineUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new MSet_LineItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}

void MSet_LineUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; j++) {
            MSet_ThresholdItemWid *item = mWid[i]->mWid[j];
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
void MSet_LineUnitWid::getCmdList(int index , int addr, QList<sSnmpSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; j++) {
            MSet_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                if(item->select()) {
                     sSnmpSetCmd cmd;
                     cmd.oid  = QString("%1.%2.%3.2.%4.%5.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(j+1).arg(i+(i==0?0:(i>=2?-1:2))+(index==0?10:6));
                     cmd.type = SNMP_STRING_TYPE;
                     cmd.value.append(QString("%1.00").arg(item->status()*(index == 0 ? 10:100)));
                     list.append(cmd);
                }
            }
        }
    }
}
