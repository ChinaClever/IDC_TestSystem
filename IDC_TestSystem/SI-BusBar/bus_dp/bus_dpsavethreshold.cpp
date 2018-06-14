#include "bus_dpsavethreshold.h"
#include "bus_sql/busdbthresholds.h"

BUS_DpSaveThreshold::BUS_DpSaveThreshold(QObject *parent)
{

}


void BUS_DpSaveThreshold::saveLoop(QStringList &list, BUS_sObjUnit &unit)
{
    BusDbThresholdItem item;

    item.bus = list.at(0);
    item.box = list.at(1);
    item.loop = unit.name;

    item.vol = unit.vol.value / COM_RATE_VOL;
    item.vol_min = unit.vol.min / COM_RATE_VOL;
    item.vol_max = unit.vol.max / COM_RATE_VOL;

    item.cur = unit.cur.value / COM_RATE_CUR;
    item.cur_min = unit.cur.min / COM_RATE_CUR;
    item.cur_max = unit.cur.max / COM_RATE_CUR;

    BusDbThresholds::bulid()->insertItem(item);
     msleep(15);
}
