#include "mpdurtutest_lineunitwid.h"
#include "ui_mpdurtutest_lineunitwid.h"

MpduRtuTest_LineUnitWid::MpduRtuTest_LineUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_LineUnitWid)
{
    ui->setupUi(this);
}

MpduRtuTest_LineUnitWid::~MpduRtuTest_LineUnitWid()
{
    delete ui;
}


void MpduRtuTest_LineUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new MpduRtuTest_LineItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}


void MpduRtuTest_LineUnitWid::getCmdList(int addr, QList<sMpduRtuTestSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; j++) {
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
