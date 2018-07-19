#include "ip_devtablewid.h"

IP_DevTableWid::IP_DevTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

void IP_DevTableWid::initWid()
{
    QString title = tr("设备实时信息");
    QStringList header;
    header << tr("设备号") << tr("相数")  << tr("开关")
           << tr("电压") << tr("电流") << tr("有功功率")
           << tr("功率因素") << tr("电能");
    initTableWid(header, 1, title);
}

void IP_DevTableWid::setAlarm(IP_RtuRecvLine &unit, int line, int row)
{
    int column=2, swAlarm=0;

    int value = unit.sw[line];
    if(value == 0) swAlarm = 2;
    setItemColor(row, column++, swAlarm);

    value = unit.vol.alarm[line];
    if(value) value = 2;
    setItemColor(row, column++, value);

    value = unit.cur.alarm[line];
    if(value) value = 2;
    setItemColor(row, column++, value);
}

void IP_DevTableWid::setObjUnit(IP_RtuRecvLine &unit, int line, QStringList &list)
{
    list << ("L"+QString::number(line+1));
    QString  str = "---";
    switch (unit.sw[line]) {
    case 0: str = tr("断开"); break;
    case 1: str = tr("闭合"); break;
    }
    list << str;

    double value = unit.vol.value[line] / COM_RATE_VOL;
    list << QString::number(value) + "V";

    value = unit.cur.value[line] / COM_RATE_CUR;
    list << QString::number(value) + "A";

    value = unit.pow[line] / COM_RATE_POW;
    list << QString::number(value) + "KVA";

    value = unit.pf[line] / COM_RATE_PF;
    list << QString::number(value);

    value = unit.ele[line] / COM_RATE_ELE;
    list << QString::number(value) + "KWh";
}


int IP_DevTableWid::updateDev(IP_Rtu_Recv &dev, int line, int row)
{
    if(dev.offLine)
    {
        for(int i=0; i<line; ++i)
        {
            QStringList list;
            list << QString::number(dev.addr);

            setObjUnit(dev.data, i, list);
            setAlarm(dev.data, i, row);
            setTableRow(row++, list);
        }
    }

    return row;
}


/**
 * @brief 数据更新入口函数
 */
void IP_DevTableWid::updateData()
{
    int row = 0;

    IpDataPackets *packets = IpDataPackets::bulid();
    for(int i=1; i<=packets->devNum; ++i)
    {
        IpDevPacket *dev = packets->getDev(i);        
        int line = dev->rtuData.data.lineNum;
        row = updateDev(dev->rtuData, line, row);
    }

    checkTableRow(row);
}
