#include "zset_lineunitwid.h"
#include "ui_zset_lineunitwid.h"

ZSet_LineUnitWid::ZSet_LineUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_LineUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

ZSet_LineUnitWid::~ZSet_LineUnitWid()
{
    delete ui;
}
void ZSet_LineUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2,ui->widget_3,ui->widget_4};
    for(int i=0; i<4; ++i) {
        mWid[i] = new ZSet_LineItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}

void ZSet_LineUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<3; j++) {
            ZSet_ThresholdItemWid *item = mWid[i]->mWid[j];
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
