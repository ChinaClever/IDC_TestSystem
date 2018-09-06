/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_dpsavetrans.h"
#include "bus_sql/busdbmodbustrans.h"

BUS_DpSaveTrans::BUS_DpSaveTrans(QObject *parent)
{

}


void BUS_DpSaveTrans::saveItem(QStringList &list, sRtuCount &unit)
{
    BusDbModbusTransItem item;

    item.bus = list.at(0);
    item.box = list.at(1);
    item.state = list.at(2);

    item.all_count = unit.count;
    item.ok_count =  unit.okCount;
    item.err_count =  unit.errCount;

    BusDbModbusTrans::bulid()->insertItem(item);
     msleep(15);
}


void BUS_DpSaveTrans::saveBox(int busId,int boxId)
{
    QString busName = BusPacketSi::bulid()->getBusName(busId);
    sDataPacket *box =  BusPacketSi::bulid()->getBox(busId, boxId);

    QString str = QObject::tr("离线");
    if(box->offLine) str = QObject::tr("在线");

    for(int i=0; i<box->data.lineNum; ++i)
    {
        QStringList list ;
        list << busName << box->name << str;

        saveItem(list, box->rtuCount);
    }
}
