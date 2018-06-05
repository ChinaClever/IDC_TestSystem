/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_transtablewid.h"

BUS_TransTableWid::BUS_TransTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

void BUS_TransTableWid::initWid()
{
    QString title = tr("传输统计信息");
    QStringList header;
    header << tr("母线") << tr("接插箱") << tr("失败次数") << tr("成功次数") << tr("总次数");
    initTableWid(header, 1, title);
}


void BUS_TransTableWid::setAlarm(int err, int row)
{
    int alarm=0;
    if(err) alarm = 2;
    setItemColor(row, 2, alarm);
}

void BUS_TransTableWid::setObjUnit(BUS_RtuCount &unit, QStringList &list)
{
    list << QString::number(unit.errCount)
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
    for(int i=1; i<=bus->boxNum; ++i) {
        row += updateBox(bus->box[i], busName, row);
    }

    return row;
}

/**
 * @brief 数据更新入口函数
 */
void BUS_TransTableWid::updateData()
{
    int row = 0;

    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *bus = BusPacketSi::bulid()->getBus(i);
        row += updateBus(bus, row);
    }

    checkTableRow(row);
}
