/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1set_envunitwid.h"
#include "ui_mv1set_envunitwid.h"

MV1Set_EnvUnitWid::MV1Set_EnvUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1Set_EnvUnitWid)
{
    ui->setupUi(this);
}

MV1Set_EnvUnitWid::~MV1Set_EnvUnitWid()
{
    delete ui;
}


void MV1Set_EnvUnitWid::initWid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new MV1Set_EnvItemWid(wid[i]);
        mWid[i]->initwid(mode, type+i);
    }
}

void MV1Set_EnvUnitWid::getCmdList(int addr, QList<sRtuSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<2; j++) {
            MV1Set_ThresholdItemWid *item = mWid[i]->mWid[j];
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
void MV1Set_EnvUnitWid::getCmdList(int index ,int addr, QList<sSnmpSetCmd> &list)
{
    for(int i=0; i<2; ++i) {
        for(int j=0; j<2; j++) {
            MV1Set_ThresholdItemWid *item = mWid[i]->mWid[j];
            if(item->select()) {
                 sSnmpSetCmd cmd;
//                 cmd.oid  = QString("%1.%2.%3.4.%4.0")
//                         .arg(MIB_OID_CLEVER)
//                         .arg(MV1_MIB_OID)
//                         .arg(addr)
//                         .arg(getIndex(index , i , j));
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
 * @param [in]  sensorThresholdNumber[0,1]最小值0，最大值1
 * @param [in]  sensorIndex[0,1]第一个传感器0，第二个1
 * @return code
 */
int MV1Set_EnvUnitWid::getIndex(int index ,int sensorThresholdNumber, int sensorIndex)
{
    int i = sensorThresholdNumber;
    int code = 0;
    code += (index == 0)?((sensorIndex == 0)? 9: 13) : ((sensorIndex == 0)? 17: 21);
    code += (i == 0 ? 0 : 3);
    return code;
}
