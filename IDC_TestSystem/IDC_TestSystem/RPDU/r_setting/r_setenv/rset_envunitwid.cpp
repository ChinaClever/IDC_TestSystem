#include "rset_envunitwid.h"
#include "ui_rset_envunitwid.h"

RSet_EnvUnitWid::RSet_EnvUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_EnvUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

RSet_EnvUnitWid::~RSet_EnvUnitWid()
{
    delete ui;
}
void RSet_EnvUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2,ui->widget_3,ui->widget_4};
    for(int i=0; i<2; ++i) {
        mWid[i] = new RSet_EnvItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}

void RSet_EnvUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<4; j++) {
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
void RSet_EnvUnitWid::getCmdList(int index ,int addr, QList<sSnmpSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<2; j++) {
            RSet_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                 sSnmpSetCmd cmd;
                 cmd.oid  = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(getIndex(index , i , j));
                 cmd.type = SNMP_STRING_TYPE;
                 cmd.value.append(QString("%1.0").arg(item->status()));
                 //qDebug()<< cmd.oid  << cmd.value;
                 list.append(cmd);
            }
        }
    }
}
/**
 * @brief getIndex
 * @param [in]  index [0,1]  温度0，湿度1
 * @param [in]  sensorThresholdNumber[0,3]最小值0，最大值1，下限值2，上限值3
 * @param [in]  sensorIndex[0,1]第一个传感器0，第二个1
 * @return code
 */
int RSet_EnvUnitWid::getIndex(int index ,int sensorThresholdNumber, int sensorIndex)
{
    int i = sensorThresholdNumber;
    int code = 0;
    code += (index == 0)? 9 : 17;
    i  += (i==0) ? i : (i >=2) ? -1 : 2 ;
    code += (sensorIndex == 0)? i : i+4;
    return code;
}
