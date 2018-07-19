/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_dpslaverecord.h"
#include "bus_sql/busdbrealrecords.h"

BUS_DpSlaveRecord::BUS_DpSlaveRecord(QObject *parent): QThread(parent)
{
    isRun  = false;
}


void BUS_DpSlaveRecord::saveLoop(QStringList &list, BUS_sObjUnit &unit)
{
    BusDbRealRecordItem item;

    item.bus = list.at(0);
    item.box = list.at(1);
    item.loop = unit.name;

    QString  str = "---";
    switch (unit.sw) {
    case 0: str = QObject::tr("断开"); break;
    case 1: str = QObject::tr("闭合"); break;
    }

    item.sw_str = str;
    item.vol = unit.vol.value / COM_RATE_VOL;
    item.cur = unit.cur.value / COM_RATE_CUR;
    item.pow = unit.pow / COM_RATE_POW;
    item.apow = unit.apPow / COM_RATE_POW;
    item.ele = unit.ele / COM_RATE_ELE;
    item.pf = unit.pf / COM_RATE_PF;

    BusDbRealRecords::bulid()->insertItem(item);
     msleep(15);
}


void BUS_DpSlaveRecord::saveBox(int busId,int boxId)
{
    QString busName = BusPacketSi::bulid()->getBusName(busId);
    sBoxData *box =  BusPacketSi::bulid()->getBox(busId, boxId);

    if(box->offLine == 0) return; //不保存
    for(int i=0; i<box->loopNum; ++i)
    {
        QStringList list ;
        list << busName << box->name ;
        saveLoop(list, box->loop[i]);
    }
}


void BUS_DpSlaveRecord::saveBus(int id)
{
    sBusData *bus =  BusPacketSi::bulid()->getBus(id);
    for(int i=0; i<=bus->boxNum; ++i) {
        saveBox(id, i);
    }
}



void BUS_DpSlaveRecord::run()
{
    if(isRun == false)
    {
        isRun  = true;

        for(int i=0; i<BUS_NUM; ++i)
            saveBus(i);

        isRun  = false;
    }
}














