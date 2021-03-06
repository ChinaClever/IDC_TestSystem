﻿/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_looptablewid.h"

BUS_LoopTableWid::BUS_LoopTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

/**
 * @brief 初始化表格
 */
void BUS_LoopTableWid::initWid()
{
    QString title = tr("接插箱回路信息");
    QStringList header;
    header << tr("母线") << tr("接插箱") << tr("回路")  << tr("开关")
           << tr("电压") << tr("电流") << tr("有功功率") << tr("视在功率")
           << tr("功率因数") << tr("电能") << tr("谐波值");
    initTableWid(header, 1, title);
}

void BUS_LoopTableWid::setAlarm(sObjData &unit, int row)
{
    int column=2, swAlarm=0;

    if(unit.sw == 0) swAlarm = 2;
    setItemColor(row, column++, swAlarm);
    setItemColor(row, column++, unit.vol.alarm);
    setItemColor(row, column++, unit.cur.alarm);
}

void BUS_LoopTableWid::setObjUnit(sObjData &unit, QStringList &list)
{
    list << unit.name;

    QString  str = "---";
    switch (unit.sw) {
    case 0: str = tr("断开"); break;
    case 1: str = tr("闭合"); break;
    }
    list << str;

    double value = unit.vol.value / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.cur.value / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.pow / COM_RATE_POW;
    list << QString::number(value) + "kVA";

    value = unit.activePow / COM_RATE_POW;
    list << QString::number(value) + "kW";

    value = unit.pf / COM_RATE_PF;
    list << QString::number(value);

    value = unit.ele / COM_RATE_ELE;
    list << QString::number(value) + "kWh";

    value = unit.wave;
    //    list << QString::number(value);
    list << "---";
}

int BUS_LoopTableWid::updateBox(sDataPacket &box, const QString &bus, int row)
{
    if(box.offLine)
    {
        for(int i=0; i<box.data.loopNum; ++i)
        {
            QStringList list;
            list << bus << box.name;

            setObjUnit(box.data.loop[i], list);
            setAlarm(box.data.loop[i], row);
            setTableRow(row++, list);
        }
    }

    return row;
}

int BUS_LoopTableWid::updateBus(sBusData *bus, int row)
{
    QString busName = bus->dev[0].name;
    for(int i=1; i<=bus->devNum; ++i) {
        row = updateBox(bus->dev[i], busName, row);
    }

    return row;
}

/**
 * @brief 数据更新入口函数
 */
void BUS_LoopTableWid::updateData()
{
    int row = 0;

    for(int i=0; i<BUS_NUM; ++i)
    {
        sBusData *bus = BusPacketSi::bulid()->getBus(i);
        if(bus->devNum) {
            row = updateBus(bus, row);
        }
    }

    checkTableRow(row);
}
