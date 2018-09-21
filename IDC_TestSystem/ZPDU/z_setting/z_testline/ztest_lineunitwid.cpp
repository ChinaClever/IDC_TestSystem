#include "ztest_lineunitwid.h"
#include "ui_ztest_lineunitwid.h"

ZTest_LineUnitWid::ZTest_LineUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_LineUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

ZTest_LineUnitWid::~ZTest_LineUnitWid()
{
    delete ui;
}
void ZTest_LineUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2,ui->widget_3,ui->widget_4};
    for(int i=0; i<4; ++i) {
        mWid[i] = new ZTest_LineItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}
void ZTest_LineUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<3; j++) {
            ZTest_ThresholdItemWid *item = mWid[i]->mWid[j];
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
