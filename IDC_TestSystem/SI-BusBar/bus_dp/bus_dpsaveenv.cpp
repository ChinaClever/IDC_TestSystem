/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_dpsaveenv.h"
#include "bus_sql/busdbenv.h"

BUS_DpSaveEnv::BUS_DpSaveEnv(QObject *parent)
{

}

void BUS_DpSaveEnv::saveLoop(QStringList &list, sDataUnit &unit)
{
    BusDbEnvItem item;

    item.bus = list.at(0);
    item.box = list.at(1);
    item.loop = list.at(2);

    item.tem = unit.value;
    item.tem_min = unit.min;
    item.tem_max = unit.max;

    BusDbEnv::bulid()->insertItem(item);
     msleep(15);
}


void BUS_DpSaveEnv::saveBox(int busId,int boxId)
{
    QString busName = BusPacketSi::bulid()->getBusName(busId);
    sDataPacket *box =  BusPacketSi::bulid()->getBox(busId, boxId);

    if(box->offLine == 0) return; //不保存
    for(int i=0; i<box->data.lineNum; ++i)
    {
        QStringList list ;
        list << busName << box->name << QObject::tr("温度%1").arg(i+1);
        saveLoop(list, box->data.env.tem[i]);
    }
}
