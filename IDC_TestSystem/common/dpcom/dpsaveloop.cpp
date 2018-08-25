/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dpsaveloop.h"

DpSaveLoop::DpSaveLoop(QObject *parent) : DpSaveOutput(parent)
{

}


void DpSaveLoop::saveLogItem(int id)
{
    sDataPacket *packet = &(mPackets->dev[id]);
    if(packet->offLine > 0)
    {
        int num = packet->data.loopNum;
        for(int i=0; i<num; ++i)
        {
            DbLoopItem item;

            item.dev_id = id;
            item.line = i+1;
            item.sw = packet->data.loop[i].sw;
            item.sw_str = tr("断开");
            if(item.sw == mSwValue) {
                item.sw_str = tr("闭合");
            }

            item.vol = packet->data.loop[i].vol.value / COM_RATE_VOL;
            item.cur = packet->data.loop[i].cur.value / COM_RATE_CUR;
            item.pow = packet->data.loop[i].pow / COM_RATE_POW;
            item.apow = packet->data.loop[i].activePow / COM_RATE_POW;
            item.pf = packet->data.loop[i].pf / COM_RATE_PF;
            item.ele = packet->data.loop[i].ele / COM_RATE_ELE;

            insertItem(item);
            msleep(LOG_DELAY);
        }
    }
}
