#include "ip_transtablewid.h"

IP_TransTableWid::IP_TransTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}


void IP_TransTableWid::initWid()
{
    QString title = tr("传输统计信息");
    QStringList header;
    header << tr("设备号") << tr("失败率") << tr("失败次数")  << tr("成功次数") << tr("总次数");
    initTableWid(header, 1, title);
}


void IP_TransTableWid::setAlarm(int err, int row)
{
    int alarm=0;
    if(err) alarm = 2;
    setItemColor(row, 1, alarm);
    setItemColor(row, 2, alarm);
}

void IP_TransTableWid::setObjUnit(IP_RtuCount &unit, QStringList &list)
{
    int count = unit.count; if(count<1) count = 1;
    list << QString::number(unit.errCount*100.0 / count, 'f', 2) +"%"
         << QString::number(unit.errCount)
         << QString::number(unit.okCount)
         << QString::number(unit.count);
}


int IP_TransTableWid::updateDev(IpDevPacket *dev, int row)
{
    QStringList list;
    list << QString::number(dev->rtuData.addr);

    setObjUnit(dev->count, list);
    setAlarm(dev->count.errCount, row);
    setTableRow(row++, list);

    return row;
}


/**
 * @brief 数据更新入口函数
 */
void IP_TransTableWid::updateData()
{
    int row = 0;

    IpDataPackets *packets = IpDataPackets::bulid();
    for(int i=0; i<packets->devNum; ++i)
    {
        IpDevPacket *dev = packets->getDev(i);
        row = updateDev(dev, row);
    }

    checkTableRow(row);
}
