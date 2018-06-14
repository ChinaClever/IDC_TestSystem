#include "bus_dpslavetrans.h"
#include "bus_sql/busdbmodbustrans.h"

BUS_DpSlaveTrans::BUS_DpSlaveTrans(QObject *parent)
{

}


void BUS_DpSlaveTrans::saveItem(QStringList &list, BUS_RtuCount &unit)
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


void BUS_DpSlaveTrans::saveBox(int busId,int boxId)
{
    QString busName = BusPacketSi::bulid()->getBusName(busId);
    sBoxData *box =  BusPacketSi::bulid()->getBox(busId, boxId);

    QString str = QObject::tr("离线");
    if(box->offLine) str = QObject::tr("在线");

    for(int i=0; i<box->lineNum; ++i)
    {
        QStringList list ;
        list << busName << box->name << str;

        saveItem(list, box->count);
    }
}
