#include "looptablewid.h"

LoopTableWid::LoopTableWid(QWidget *parent) : OutputTableWid(parent)
{

}

void LoopTableWid::initWid()
{
    QString title = tr("设备回路实时相信息");
    QStringList header;
    header << tr("设备号") << tr("回路")  << tr("开关")
           << tr("电压") << tr("电流") << tr("功率") << tr("电能");
    initTableWid(header, 1, title);
}


int LoopTableWid::updateDev(sDataPacket *dev, int row)
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
