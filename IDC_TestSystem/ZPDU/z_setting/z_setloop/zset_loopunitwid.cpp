#include "zset_loopunitwid.h"
#include "ui_zset_loopunitwid.h"

ZSet_LoopUnitWid::ZSet_LoopUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_LoopUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

ZSet_LoopUnitWid::~ZSet_LoopUnitWid()
{
    delete ui;
}
void ZSet_LoopUnitWid::initWid(int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2,ui->widget_3,ui->widget_4};
    for(int i=0; i<4; ++i) {
        mWid[i] = new ZSet_LoopItemWid(wid[i]);
        mWid[i]->initwid(type+i);
    }
}

void ZSet_LoopUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<6; j++) {
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
void ZSet_LoopUnitWid::getCmdList(int addr, QList<sSnmpSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<6; j++) {
            ZSet_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                 sSnmpSetCmd cmd;
                 cmd.oid  = QString("%1.%2.%3.3.%4.%5.0").arg(MIB_OID_CLEVER).arg(Z_MIB_OID).arg(addr).arg(j+1).arg(i+7);
                 cmd.type = SNMP_STRING_TYPE;
                 cmd.value.append(QString("%1.00").arg(item->status()*LOOPCURRATE));
                 list.append(cmd);
            }
        }
    }
}
