#include "mpdurtutest_envunitwid.h"
#include "ui_mpdurtutest_envunitwid.h"

MpduRtuTest_EnvUnitWid::MpduRtuTest_EnvUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_EnvUnitWid)
{
    ui->setupUi(this);
}

MpduRtuTest_EnvUnitWid::~MpduRtuTest_EnvUnitWid()
{
    delete ui;
}



void MpduRtuTest_EnvUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new MpduRtuTest_EnvItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}


void MpduRtuTest_EnvUnitWid::getCmdList(int addr, QList<sMpduRtuTestSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<2; j++) {
            MpduRtuTest_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                 sMpduRtuTestSetCmd cmd;
                 cmd.addr = addr;
                 cmd.reg =  mWid[i]->mReg + j;
                 cmd.value = item->status();
                 list.append(cmd);
            }
        }
    }
}
