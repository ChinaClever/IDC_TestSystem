/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_bustablewid.h"

BUS_BusTableWid::BUS_BusTableWid(QWidget *parent) : BUS_LoopTableWid(parent)
{
    initWid();
}

void BUS_BusTableWid::initWid()
{
    QString title = tr("始端箱实时信息");
    QStringList header;
    header << tr("母线") << tr("输入相")  << tr("开关")
           << tr("电压") << tr("电流") << tr("有功功率") << tr("视在功率")
           << tr("功率因素") << tr("电能") << tr("谐波值");
    initTableWid(header, 1, title);
}

void BUS_BusTableWid::setLineName(sBoxData &box)
{
    char array [2] = {0,0};

    for(int i=0; i<box.loopNum; ++i) {
        char *buf = box.loop[i].name;
        array[0] = 'A' + i;

        QString name = array;
        if(box.dc==0) {
            name = "D" + QString::number(i+1);
        }

        QByteArray ba = name.toLatin1();
        char *mm = ba.data();
        strcpy(buf,mm);
    }
}


int BUS_BusTableWid::updateBox(sBoxData &box, const QString &bus, int row)
{
    if(box.offLine)
    {
        for(int i=0; i<box.loopNum; ++i)
        {
            QStringList list;
            list << box.name;
            if(box.loop[i].vol.value > 20)
            {
                setLineName(box);
                setObjUnit(box.loop[i], list);
                setAlarm(box.loop[i], row);
                setTableRow(row++, list);
            } else {
                clearRow(row++);
            }
        }
    }

    return row;
}

int BUS_BusTableWid::updateBus(sBusData *bus, int row)
{
    return updateBox(bus->box[0], "", row);;
}
