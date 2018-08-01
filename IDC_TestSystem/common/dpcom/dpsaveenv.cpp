/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dpsaveenv.h"
#include "sqlcom/dbenv.h"

DpSaveEnv::DpSaveEnv(QObject *parent) : DpSaveRecord(parent)
{

}


void DpSaveEnv::saveLogItem(int id)
{
    sDataPacket *packet = &(mPackets->dev[id]);
    if(packet->offLine > 0)
    {
        int  num = packet->data.env.envNum;
        for(int i=0; i<num; ++i) {
            DbEnvItem item;

            item.dev_id = id;
            item.tem = packet->data.env.tem[i].value;
            item.tem_min = packet->data.env.tem[i].min;
            item.tem_max = packet->data.env.tem[i].max;
            item.hum = packet->data.env.hum[i].value;
            item.hum_min = packet->data.env.hum[i].min;
            item.hum_max = packet->data.env.hum[i].max;

            insertItem(item);
            msleep(LOG_DELAY);
        }
    }

}
