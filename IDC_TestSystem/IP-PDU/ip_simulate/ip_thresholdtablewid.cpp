/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_thresholdtablewid.h"

IP_ThresholdTableWid::IP_ThresholdTableWid(QWidget *parent) : IP_DevTableWid(parent)
{
    initWid();
}

void IP_ThresholdTableWid::initWid()
{
    QString title = tr("设备阈值信息");
    QStringList header;
    header << tr("设备号") << tr("相数")
           << tr("电压") << tr("电压下限") << tr("电压上限")
           << tr("电流") << tr("电流下限") << tr("电流上限");
    initTableWid(header, 1, title);
}


void IP_ThresholdTableWid::setAlarm(IP_RtuRecvLine &unit, int line, int row)
{
    int value = unit.vol.alarm[line];
    if(value) value = 2;
    setItemColor(row, 2, value);

    value = unit.cur.alarm[line];
    if(value) value = 2;
    setItemColor(row, 5, value);
}


void IP_ThresholdTableWid::setObjUnit(IP_RtuRecvLine &unit, int line, QStringList &list)
{
    list << ("L"+QString::number(line+1));
    double value = unit.vol.value[line] / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.vol.min[line] / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.vol.max[line] / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.cur.value[line] / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.cur.min[line] / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.cur.max[line] / COM_RATE_CUR;
    list << QString::number(value) + "A";

}
