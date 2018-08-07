/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mtest_lineunitwid.h"
#include "ui_mtest_lineunitwid.h"

MTest_LineUnitWid::MTest_LineUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MTest_LineUnitWid)
{
    ui->setupUi(this);
}

MTest_LineUnitWid::~MTest_LineUnitWid()
{
    delete ui;
}


void MTest_LineUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new MTest_LineItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}


void MTest_LineUnitWid::getCmdList(int addr, QList<sMTestRtuSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; j++) {
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
