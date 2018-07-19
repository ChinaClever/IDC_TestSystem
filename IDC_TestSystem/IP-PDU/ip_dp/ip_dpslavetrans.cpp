#include "ip_dpslavetrans.h"
#include "ip_sql/ipdbmodbustrans.h"

IP_DpSlaveTrans::IP_DpSlaveTrans(QObject *parent) : IP_DpSlaveRecord(parent)
{

}


void IP_DpSlaveTrans::saveLogItem(int id)
{
    IpDbModbusTransItem item;

    IpDevPacket *dev = IpDataPackets::bulid()->getDev(id);
    IP_RtuCount *packet = &(dev->count);

    item.dev_id = id;
    item.all_count = packet->count;
    item.ok_count = packet->okCount;
    item.err_count = packet->errCount;

    QString str =tr("离线");
    if(dev->rtuData.offLine)
        str =tr("在线");
    item.state = str;

    IpDbModbusTrans::bulid()->insertItem(item);
    msleep(LOG_DELAY);
}
