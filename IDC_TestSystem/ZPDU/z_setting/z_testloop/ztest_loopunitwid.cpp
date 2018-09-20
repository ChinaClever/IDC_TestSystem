#include "ztest_loopunitwid.h"
#include "ui_ztest_loopunitwid.h"

ZTest_LoopUnitWid::ZTest_LoopUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_LoopUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

ZTest_LoopUnitWid::~ZTest_LoopUnitWid()
{
    delete ui;
}
void ZTest_LoopUnitWid::initWid(int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2,ui->widget_3,ui->widget_4};
    for(int i=0; i<4; ++i) {
        mWid[i] = new ZTest_LoopItemWid(wid[i]);
        mWid[i]->initwid(type+i);
    }
}
void ZTest_LoopUnitWid::getCmdList(int addr, QList<sZTestRtuSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<6; j++) {
            ZTest_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                 sZTestRtuSetCmd cmd;
                 cmd.addr = addr;
                 cmd.reg =  mWid[i]->mReg + j;
                 cmd.value = item->status();
                 list.append(cmd);
            }
        }
    }
}
