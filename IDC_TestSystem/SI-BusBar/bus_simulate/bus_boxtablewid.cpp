/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_boxtablewid.h"

BUS_BoxTableWid::BUS_BoxTableWid(QWidget *parent) : BUS_LoopTableWid(parent)
{
    initWid();
}

void BUS_BoxTableWid::initWid()
{
    QString title = tr("接端箱支路信息");
    QStringList header;
    header << tr("母线") << tr("接插箱") << tr("支路")  << tr("开关")
           << tr("电压") << tr("电流") << tr("有功功率") << tr("视在功率")
           << tr("功率因素") << tr("电能") << tr("谐波值");
    initTableWid(header, 1, title);
}

void BUS_BoxTableWid::setLineName(sBoxData &box)
{
    char array [2] = {0,0};
    for(int i=0; i<box.lineNum; ++i) {
        char *buf = box.line[i].name;
        array[0] = 'A' + i;

        QString name = array;
        if(box.dc==0) {
            name = "D" + QString::number(i+1);
        }
        box.line[i].sw = 1;

        QByteArray ba = name.toLatin1();
        char *mm = ba.data();
        strcpy(buf,mm);
    }
}

int BUS_BoxTableWid::updateBox(sBoxData &box, const QString &bus, int row)
{
    if(box.offLine)
    {
        for(int i=0; i<box.lineNum; ++i)
        {
            QStringList list;
            list << bus << box.name;

            setLineName(box);
            setObjUnit(box.line[i], list);
            setTableRow(row++, list);
        }
    }

    return row;
}
