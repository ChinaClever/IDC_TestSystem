#include "rset_loopunitwid.h"
#include "ui_rset_loopunitwid.h"

RSet_LoopUnitWid::RSet_LoopUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_LoopUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

RSet_LoopUnitWid::~RSet_LoopUnitWid()
{
    delete ui;
}
void RSet_LoopUnitWid::initWid(int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2,ui->widget_3,ui->widget_4};
    for(int i=0; i<4; ++i) {
        mWid[i] = new RSet_LoopItemWid(wid[i]);
        mWid[i]->initwid(type+i);
    }
}

void RSet_LoopUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<6; j++) {
            RSet_ThresholdItemWid *item = mWid[i]->mWid[j];
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
void RSet_LoopUnitWid::getCmdList(int addr, QList<sSnmpSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<6; j++) {
            RSet_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                 sSnmpSetCmd cmd;
                 cmd.oid  = QString("%1.%2.%3.3.%4.%5.0")
                         .arg(MIB_OID_CLEVER)
                         .arg(R_MIB_OID)
                         .arg(addr)
                         .arg(j+1)
                         .arg(i==0?i+7:(i==1)?i+9:i+7-1);
                 cmd.type = SNMP_STRING_TYPE;
                 cmd.value.append(QString("%1.00").arg(item->status()*LOOPCURRATE));
                 list.append(cmd);
            }
        }
    }
}
