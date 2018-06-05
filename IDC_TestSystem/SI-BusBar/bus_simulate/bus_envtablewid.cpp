/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_envtablewid.h"

BUS_EnvTableWid::BUS_EnvTableWid(QWidget *parent) : BUS_LoopTableWid(parent)
{
    initWid();
}

void BUS_EnvTableWid::initWid()
{
    QString title = tr("接插箱环境信息");
    QStringList header;
    header << tr("母线") << tr("接插箱") << tr("传感器")
            << tr("温度") << tr("温度下限") << tr("温度上限");
    initTableWid(header, 1, title);
}


void BUS_EnvTableWid::setAlarm(BUS_sDataUnit &unit, int row)
{
    setItemColor(row, 3, unit.alarm);
}


void BUS_EnvTableWid::setObjUnit(BUS_sDataUnit &unit, QStringList &list)
{
    list << QString::number(unit.value) + " ℃"
         << QString::number(unit.min) + " ℃"
         << QString::number(unit.max) + " ℃";
}


int BUS_EnvTableWid::updateBox(sBoxData &box, const QString &bus, int row)
{
    if(box.offLine)
    {
        for(int i=0; i<box.loopNum; ++i)
        {
            QStringList list;
            list << bus << box.name;
            list << tr("温度%1").arg(i+1);

            setObjUnit(box.env[i].tem, list);
            setAlarm(box.env[i].tem, row);
            setTableRow(row++, list);
        }
    }

    return row;
}
