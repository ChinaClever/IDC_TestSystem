/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_transtablewid.h"

BUS_TransTableWid::BUS_TransTableWid(QWidget *parent) : BUS_LoopTableWid(parent)
{
    initWid();
}

void BUS_TransTableWid::initWid()
{
    QString title = tr("传输统计信息");
    QStringList header;
    header << tr("母线") << tr("接插箱") << tr("连续失败次数") << tr("失败率") << tr("失败次数")  << tr("成功次数") << tr("总次数");
    initTableWid(header, 1, title);
}


void BUS_TransTableWid::setAlarm(int err, int row)
{
    int alarm=0;
    if(err) alarm = 2;
    setItemColor(row, 3, alarm);
}

void BUS_TransTableWid::setObjUnit(BUS_RtuCount &unit, QStringList &list)
{
    int count = unit.count; if(count<1) count = 1;
    list << QString::number(unit.longCount)
         << QString::number(unit.errCount*100.0 / count, 'f', 2) +"%"
         << QString::number(unit.errCount)
         << QString::number(unit.okCount)
         << QString::number(unit.count);
}


int BUS_TransTableWid::updateBox(sBoxData &box, const QString &bus, int row)
{
    QStringList list;
    list << bus << box.name;

    setObjUnit(box.count, list);
    setAlarm(box.count.errCount, row);
    setTableRow(row++, list);

    return row;
}

int BUS_TransTableWid::updateBus(sBusData *bus, int row)
{
    QString busName = bus->box[0].name;
    for(int i=0; i<=bus->boxNum; ++i) {
        row = updateBox(bus->box[i], busName, row);
    }

    return row;
}
