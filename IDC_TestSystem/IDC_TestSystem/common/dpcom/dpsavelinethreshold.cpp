/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dpsavelinethreshold.h"
#include "sqlcom/dblinethresholds.h"

DpSaveLineThreshold::DpSaveLineThreshold(QObject *parent) : DpSaveRecord(parent)
{

}


void DpSaveLineThreshold::saveLogItem(int id)
{
    sDataPacket *packet = &(mPackets->dev[id]);
    if(packet->offLine > 0)
    {
        int line = packet->data.lineNum;
        for(int i=0; i<line; ++i)
        {
            DbLineThresholdItem item;

            item.dev_id = id;
            item.line = i+1;
            item.vol = packet->data.line[i].vol.value / COM_RATE_VOL;
            item.vol_min = packet->data.line[i].vol.min / COM_RATE_VOL;
            item.vol_max = packet->data.line[i].vol.max / COM_RATE_VOL;

            item.cur = packet->data.line[i].cur.value / COM_RATE_CUR;
            item.cur_min = packet->data.line[i].cur.min / COM_RATE_CUR;
            item.cur_max = packet->data.line[i].cur.max / COM_RATE_CUR;

            insertItem(item);
            msleep(LOG_DELAY);
        }
    }
}
