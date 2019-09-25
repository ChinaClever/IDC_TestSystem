#include "rset_lineunitwid.h"
#include "ui_rset_lineunitwid.h"

RSet_LineUnitWid::RSet_LineUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_LineUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

RSet_LineUnitWid::~RSet_LineUnitWid()
{
    delete ui;
}
void RSet_LineUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2,ui->widget_3,ui->widget_4};
    for(int i=0; i<2; ++i) {
        mWid[i] = new RSet_LineItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}

void RSet_LineUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; j++) {
            RSet_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                sRtuSetCmd cmd;
                cmd.addr = addr;
                cmd.reg =  mWid[i]->mReg + j;
                int rate = 10;
                if(mWid[i]->mMode) rate = 1;//电压rate 1 电流rate 10
                cmd.value = item->status()*rate;
                list.append(cmd);
            }
        }
    }
}
void RSet_LineUnitWid::getCmdList(int index , int addr, QList<sSnmpSetCmd> &list)
{//index == 0 电压  index == 1 电流
    for(int i=0; i<2; ++i) {// i==0 最小值 // i==1 最大值
        for(int j=0; j<3; j++) {
            RSet_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                sSnmpSetCmd cmd;
                cmd.oid  = QString("%1.%2.%3.1.%4.%5.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(j+3).arg(index == 1?(i==0?6:7):(i==0?8:9));
                cmd.type = SNMP_STRING_TYPE;
                qDebug()<<"oid"<<cmd.oid;
                cmd.value.append(QString("%1.0").arg(item->status()*(index == 0 ? 1:10)));//不清楚是否还要倍率
                list.append(cmd);
            }
        }
    }
}
