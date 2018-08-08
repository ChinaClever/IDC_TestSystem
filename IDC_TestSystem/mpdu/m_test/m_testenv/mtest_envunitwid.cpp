/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mtest_envunitwid.h"
#include "ui_mtest_envunitwid.h"

MTest_EnvUnitWid::MTest_EnvUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MTest_EnvUnitWid)
{
    ui->setupUi(this);
}

MTest_EnvUnitWid::~MTest_EnvUnitWid()
{
    delete ui;
}


void MTest_EnvUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new MTest_EnvItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}


void MTest_EnvUnitWid::getCmdList(int addr, QList<sMTestRtuSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<2; j++) {
            MTest_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                 sMTestRtuSetCmd cmd;
                 cmd.addr = addr;
                 cmd.reg =  mWid[i]->mReg + j;
                 cmd.value = item->status();
                 list.append(cmd);
            }
        }
    }
}
