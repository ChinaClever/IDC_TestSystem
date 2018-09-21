#include "zset_envunitwid.h"
#include "ui_zset_envunitwid.h"

ZSet_EnvUnitWid::ZSet_EnvUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_EnvUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

ZSet_EnvUnitWid::~ZSet_EnvUnitWid()
{
    delete ui;
}
void ZSet_EnvUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2,ui->widget_3,ui->widget_4};
    for(int i=0; i<4; ++i) {
        mWid[i] = new ZSet_EnvItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}

void ZSet_EnvUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<2; j++) {
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
void ZSet_EnvUnitWid::getCmdList(int index ,int addr, QList<sSnmpSetCmd> &list)
{
    for(int i=0; i<4; ++i) {
        for(int j=0; j<2; j++) {
            ZSet_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                 sSnmpSetCmd cmd;
                 cmd.oid  = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(Z_MIB_OID).arg(addr).arg(getIndex(index , i , j));
                 cmd.type = SNMP_STRING_TYPE;
                 cmd.value.append(QString("%1.0").arg(item->status()));
                 qDebug()<< cmd.oid  << cmd.value;
                 list.append(cmd);
            }
        }
    }
}
int ZSet_EnvUnitWid::getIndex(int index ,int i, int j)
{
    int code = 0;
    code += (index == 0)? 9 : 17;
    i  += (i==0) ? i : (i >=2) ? -1 : 2 ;
    code += (j == 0)? i : i+4;
    return code;
}
