/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "transtablewid.h"

TransTableWid::TransTableWid(QWidget *parent) : LineTableWid(parent)
{
    initWid();
}

void TransTableWid::initWid()
{
    QString title = tr("传输统计信息");
    QStringList header;
    header << tr("设备号") << tr("失败率") << tr("失败次数")  << tr("成功次数") << tr("总次数");
    initTableWid(header, 1, title);
}

void TransTableWid::setAlarm(int err, int row)
{
    int alarm=0;
    if(err) alarm = 2;
    setItemColor(row, 1, alarm);
    setItemColor(row, 2, alarm);
}

void TransTableWid::setObjUnit(sRtuCount &unit, QStringList &list)
{
    int count = unit.count; if(count<1) count = 1;
    list << QString::number(unit.errCount*100.0 / count, 'f', 2) +"%"
         << QString::number(unit.errCount)
         << QString::number(unit.okCount)
         << QString::number(unit.count);
}

int TransTableWid::updateDev(sDataPacket *dev, int row)
{
    QStringList list;
    list << QString::number(dev->id);

    setObjUnit(dev->rtuCount, list);
    setAlarm(dev->rtuCount.errCount, row);
    setTableRow(row++, list);

    return row;
}


