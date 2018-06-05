#include "bus_thresholdtablewid.h"

BUS_ThresholdTableWid::BUS_ThresholdTableWid(QWidget *parent) : BUS_LoopTableWid(parent)
{
    initWid();
}

void BUS_ThresholdTableWid::initWid()
{
    QString title = tr("接插箱回路信息");
    QStringList header;
    header << tr("母线") << tr("接插箱") << tr("回路")
           << tr("电压") << tr("电压下限") << tr("电压上限")
           << tr("电流") << tr("电流下限") << tr("电流上限");
    initTableWid(header, 1, title);
}


void BUS_ThresholdTableWid::setAlarm(BUS_sObjUnit &unit, int row)
{
    setItemColor(row, 3, unit.vol.alarm);
    setItemColor(row, 6, unit.cur.alarm);
}


void BUS_ThresholdTableWid::setObjUnit(BUS_sObjUnit &unit, QStringList &list)
{
    list << unit.name;

    double value = unit.vol.value / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.vol.min / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.vol.max / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.cur.value / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.cur.min / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.cur.max / COM_RATE_CUR;
    list << QString::number(value) + "A";
}

