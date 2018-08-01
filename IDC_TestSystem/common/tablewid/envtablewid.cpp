/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "envtablewid.h"

EnvTableWid::EnvTableWid(QWidget *parent) : LineTableWid(parent)
{
    initWid();
}


void EnvTableWid::initWid()
{
    QString title = tr("设备环境信息");
    QStringList header;
    header << tr("设备号") << tr("温度") << tr("温度下限") << tr("温度上限")
           << tr("湿度") << tr("湿度下限") << tr("湿度上限");
    initTableWid(header, 1, title);
}


void EnvTableWid::setAlarm(sEnvData &unit, int id, int row)
{
    int value = unit.tem[id].alarm;
    if(value) value = 2;
    setItemColor(row, 1, value);

    value = unit.hum[id].alarm;
    if(value) value = 2;
    setItemColor(row, 4, value);
}


void EnvTableWid::setObjUnit(sEnvData &unit, int id, QStringList &list)
{
    double value = unit.tem[id].value / COM_RATE_TEM;
    list << QString::number(value) + " ℃";

    value = unit.tem[id].min / COM_RATE_TEM;
    list << QString::number(value) + " ℃";

    value = unit.tem[id].max / COM_RATE_TEM;
    list << QString::number(value) + " ℃";

    value = unit.hum[id].value / COM_RATE_HUM;
    list << QString::number(value) + " %";

    value = unit.hum[id].min / COM_RATE_HUM;
    list << QString::number(value) + " %";

    value = unit.hum[id].max / COM_RATE_HUM;
    list << QString::number(value) + " %";
}


int EnvTableWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        int num = dev->data.env.envNum;
        for(int i=0; i<num; ++i)
        {
            QStringList list;
            list << QString::number(dev->id);
            list << ("传感器"+QString::number(i+1));
            setObjUnit(dev->data.env, i,  list);
            setAlarm(dev->data.env, i,  row);
            setTableRow(row++, list);
        }
    }

    return row;
}

