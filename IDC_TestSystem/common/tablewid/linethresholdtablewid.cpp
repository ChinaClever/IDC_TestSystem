/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "linethresholdtablewid.h"

LineThresholdTableWid::LineThresholdTableWid(QWidget *parent) : LineTableWid(parent)
{
     initWid();
}


void LineThresholdTableWid::initWid()
{
    QString title = tr("设备阈值信息");
    QStringList header;
    header << tr("设备号") << tr("相数")
           << tr("电压") << tr("电压下限") << tr("电压上限")
           << tr("电流") << tr("电流下限") << tr("电流上限");
    initTableWid(header, 1, title);
}


void LineThresholdTableWid::setAlarm(sObjData &unit, int row)
{
    int value = unit.vol.alarm;
    if(value) value = 2;
    setItemColor(row, 2, value);

    value = unit.cur.alarm;
    if(value) value = 2;
    else value = unit.cur.crAlarm;
    setItemColor(row, 5, value);
}

double LineThresholdTableWid::autoRate(int vol)
{
    double ret = 1;
    if(vol > 1000 && vol < 3000) {
        ret = 0.1;
    }
    mRate = ret;

    return ret;
}

void LineThresholdTableWid::setObjUnit(sObjData &unit, QStringList &list)
{
    autoRate(unit.vol.value);
    double value = unit.vol.value * mRate/ COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.vol.min * mRate/ COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.vol.max * mRate/ COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.cur.value * mRate/ COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.cur.min * mRate/ COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.cur.max * mRate/ COM_RATE_CUR;
    list << QString::number(value) + "A";
}
