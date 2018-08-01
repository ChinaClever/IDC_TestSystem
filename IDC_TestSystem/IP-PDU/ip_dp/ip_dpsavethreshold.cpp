/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_dpsavethreshold.h"
#include "ip_sql/ipdbthresholds.h"

IP_DpSaveThreshold::IP_DpSaveThreshold(QObject *parent) : IP_DpSlaveRecord(parent)
{

}


void IP_DpSaveThreshold::saveLogItem(int id)
{
    IpDevPacket *dev = IpDataPackets::bulid()->getDev(id);
    IP_Rtu_Recv *packet = &(dev->rtuData);
    if(packet->offLine > 0)
    {
        int line = packet->data.lineNum;
        for(int i=0; i<line; ++i)
        {
            DbLineThresholdItem item;

            item.dev_id = id;
            item.line = i+1;
            item.vol = packet->data.vol.value[i] / COM_RATE_VOL;
            item.vol_min = packet->data.vol.min[i] / COM_RATE_VOL;
            item.vol_max = packet->data.vol.max[i] / COM_RATE_VOL;

            item.cur = packet->data.cur.value[i] / COM_RATE_CUR;
            item.cur_min = packet->data.cur.min[i] / COM_RATE_CUR;
            item.cur_max = packet->data.cur.max[i] / COM_RATE_CUR;

            IpDbThresholds::bulid()->insertItem(item);
            msleep(LOG_DELAY);
        }
    }
}
