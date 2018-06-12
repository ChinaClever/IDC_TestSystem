/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_dpalarm.h"

BUS_DpAlarm::BUS_DpAlarm(QObject *parent) : QObject(parent)
{

}


void BUS_DpAlarm::alarmDataUnit(BUS_sDataUnit &unit, bool cr)
{
    if((unit.value < unit.min) || (unit.value > unit.max))
    {
        if(unit.alarm == 0)
            unit.alarm = 1;
    } else {
        unit.alarm = 0;
    }

    if(cr) {
        if((unit.value < unit.crMin) || (unit.value > unit.crMax))
        {
            if(unit.crAlarm == 0)
                unit.crAlarm = 1;
        } else
            unit.crAlarm = 0;
    }
}


void BUS_DpAlarm::boxAlarm(sBoxData &box)
{
    if(box.offLine > 0)
    {
        for(int i=0; i<box.loopNum; ++i) {
            alarmDataUnit(box.loop[i].cur); // 回路是否有告警
            alarmDataUnit(box.loop[i].vol); // 回路是否有告警
        }

        int num = 3;
        if(!box.dc) num = box.rate;
        for(int i=0; i<num; ++i) {
            alarmDataUnit(box.env[i].tem);
        }
    }
}


void BUS_DpAlarm::busAlarm(sBusData *bus)
{
    for(int i=0; i<=bus->boxNum; ++i) {
        boxAlarm(bus->box[i]);
    }
}


void BUS_DpAlarm::alarm()
{
    for(int i=0; i<BUS_NUM; ++i) {
        busAlarm(BusPacketSi::bulid()->getBus(i));
    }
}
