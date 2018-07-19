#include "ip_dpslaveenv.h"
#include "ip_sql/ipdbenv.h"

IP_DpSlaveEnv::IP_DpSlaveEnv(QObject *parent) : IP_DpSlaveRecord(parent)
{

}


void IP_DpSlaveEnv::saveLogItem(int id)
{
    IpDevPacket *dev = IpDataPackets::bulid()->getDev(id);
    IP_Rtu_Recv *packet = &(dev->rtuData);
    if(packet->offLine > 0)
    {
        IpDbEnvItem item;

        item.dev_id = id;
        item.tem = packet->data.tem.value[0];
        item.tem_min = packet->data.tem.min[0];
        item.tem_max = packet->data.tem.max[0];
        item.hum = packet->data.hum.value[0];
        item.hum_min = packet->data.hum.min[0];
        item.hum_max = packet->data.hum.max[0];

        IpDbEnv::bulid()->insertItem(item);
        msleep(LOG_DELAY);
    }

}
