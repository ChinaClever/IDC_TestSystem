#include "ip_envtablewid.h"

IP_EnvTableWid::IP_EnvTableWid(QWidget *parent) : IP_DevTableWid(parent)
{
    initWid();
}


void IP_EnvTableWid::initWid()
{
    QString title = tr("设备环境信息");
    QStringList header;
    header << tr("设备号") << tr("温度") << tr("温度下限") << tr("温度上限")
           << tr("湿度") << tr("湿度下限") << tr("湿度上限");
    initTableWid(header, 1, title);
}


void IP_EnvTableWid::setAlarm(IP_RtuRecvLine &unit, int line, int row)
{
    int value = unit.tem.alarm[line];
    if(value) value = 2;
    setItemColor(row, 1, value);

    value = unit.hum.alarm[line];
    if(value) value = 2;
    setItemColor(row, 4, value);
}


void IP_EnvTableWid::setObjUnit(IP_RtuRecvLine &unit, int line, QStringList &list)
{

    double value = unit.tem.value[line] / COM_RATE_TEM;
    list << QString::number(value) + " ℃";

    value = unit.tem.min[line] / COM_RATE_TEM;
    list << QString::number(value) + " ℃";

    value = unit.tem.max[line] / COM_RATE_TEM;
    list << QString::number(value) + " ℃";

    value = unit.hum.value[line] / COM_RATE_HUM;
    list << QString::number(value) + " %";

    value = unit.hum.min[line] / COM_RATE_HUM;
    list << QString::number(value) + " %";

    value = unit.hum.max[line] / COM_RATE_HUM;
    list << QString::number(value) + " %";
}


void IP_EnvTableWid::updateData()
{
    int row = 0;

    IpDataPackets *packets = IpDataPackets::bulid();
    for(int i=0; i<packets->devNum; ++i)
    {
        IpDevPacket *dev = packets->getDev(i);
        row = updateDev(dev->rtuData, 1, row);
    }

    checkTableRow(row);
}
