/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "outputtablewid.h"

OutputTableWid::OutputTableWid(QWidget *parent) : LineTableWid(parent)
{
    initWid();
}


void OutputTableWid::initWid()
{
    QString title = tr("输出位实时相信息");
    QStringList header;
    header << tr("设备号") << tr("输出位")  << tr("开关")
           << tr("电压") << tr("电流") << tr("功率")
           << tr("功率因数") << tr("电能");
    initTableWid(header, 1, title);
}

double OutputTableWid::autoRate(int vol)
{
    double ret = 1;
    if(vol > 1000 && vol < 3000) {
        ret = 0.1;
    }
    mRate = ret;

    return ret;
}

int OutputTableWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        int line = dev->data.outputNum;
        autoRate(dev->data.line[0].vol.value);
        for(int i=0; i<line; ++i)
        {
            QStringList list;
            list << QString::number(dev->id);
            QString str = dev->data.output[i].name;
            if(str.isEmpty())
                list << ("Output "+QString::number(i+1));
            else
                list << str;

            setObjUnit(dev->data.output[i],  list);
            setAlarm(dev->data.output[i],  row);
            setTableRow(row++, list);
        }
    }

    return row;
}
