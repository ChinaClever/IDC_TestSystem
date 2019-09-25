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
void ZSet_LineUnitWid::getCmdList(int index , int addr, QList<sSnmpSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<3; j++) {
            ZSet_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                sSnmpSetCmd cmd;
                cmd.oid  = QString("%1.%2.%3.2.%4.%5.0").arg(MIB_OID_CLEVER).arg(Z_MIB_OID).arg(addr).arg(j+1).arg(i+(i==0?0:(i>=2?-1:2))+(index==0?10:6));
                cmd.type = SNMP_STRING_TYPE;
                cmd.value.append(QString("%1.00").arg(item->status()*(index == 0 ? 1:100)));
                list.append(cmd);
            }
        }
    }
}
