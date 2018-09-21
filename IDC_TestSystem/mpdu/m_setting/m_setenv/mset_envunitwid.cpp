/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_envunitwid.h"
#include "ui_mset_envunitwid.h"

MSet_EnvUnitWid::MSet_EnvUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_EnvUnitWid)
{
    ui->setupUi(this);
}

MSet_EnvUnitWid::~MSet_EnvUnitWid()
{
    delete ui;
}


void MSet_EnvUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new MSet_EnvItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}

void MSet_EnvUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<2; j++) {
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
