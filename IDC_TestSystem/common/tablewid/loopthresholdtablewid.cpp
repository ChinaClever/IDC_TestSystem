/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "loopthresholdtablewid.h"

LoopThresholdTableWid::LoopThresholdTableWid(QWidget *parent) : OutputThresholdTableWid(parent)
{

}

void LoopThresholdTableWid::initWid()
{
   QString title = tr("回路阈值信息");
   QStringList header;
   header << tr("设备号") << tr("回路")
          << tr("电流") << tr("最小值") << tr("临界下限")
          << tr("临界上限") << tr("最大值");
   initTableWid(header, 1, title);
}


int LoopThresholdTableWid::updateDev(sDataPacket *dev, int row)
{
    if(dev->offLine)
    {
        int line = dev->data.loopNum;
        for(int i=0; i<line; ++i)
        {
            QStringList list;
            list << QString::number(dev->id);
            QString str = dev->data.loop[i].name;
            if(str.isEmpty()) list << ("C "+QString::number(i+1));

            setObjUnit(dev->data.loop[i],  list);
            setAlarm(dev->data.loop[i],  row);
            setTableRow(row++, list);
        }
    }

    return row;
}
