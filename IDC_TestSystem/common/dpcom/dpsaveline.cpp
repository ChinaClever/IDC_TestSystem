/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dpsaveline.h"
#include "sqlcom/dblinerecords.h"

DpSaveLine::DpSaveLine(QObject *parent) : DpSaveRecord(parent)
{

}


void DpSaveLine::saveLogItem(int id)
{
    sDataPacket *packet = &(mPackets->dev[id]);
    if(packet->offLine > 0)
    {
        int line = packet->data.lineNum;
        for(int i=0; i<line; ++i)
        {
            DbLineRecordItem item;

            item.dev_id = id;
            item.line = i+1;
            item.sw = packet->data.line[i].sw;
            if(item.sw) {
                item.sw_str = tr("断开");
            } else  {
                item.sw_str = tr("闭合");
            }

            item.vol = packet->data.line[i].vol.value / COM_RATE_VOL;
            item.cur = packet->data.line[i].cur.value / COM_RATE_CUR;
            item.pow = packet->data.line[i].pow / COM_RATE_POW;
            item.apow = packet->data.line[i].activePow / COM_RATE_POW;
            item.pf = packet->data.line[i].pf / COM_RATE_PF;
            item.ele = packet->data.line[i].ele / COM_RATE_ELE;

            insertItem(item);
            msleep(LOG_DELAY);
        }
    }
}
