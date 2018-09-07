#include "eload_dpsavelinethreshold.h"

ELoad_DpSaveLineThreshold::ELoad_DpSaveLineThreshold(QObject *parent) : DpSaveLineThreshold(parent)
{

}


void ELoad_DpSaveLineThreshold::saveLogItem(int id)
{
    sDataPacket *packet = &(mPackets->dev[id]);
    if(packet->offLine > 0)
    {
        int line = packet->data.inputNum;
        for(int i=0; i<line; ++i)
        {
            DbLineThresholdItem item;

            item.dev_id = id;
            item.line = i+1;
            item.vol = packet->data.input[i].vol.value / COM_RATE_VOL;
            item.vol_min = packet->data.input[i].vol.min / COM_RATE_VOL;
            item.vol_max = packet->data.input[i].vol.max / COM_RATE_VOL;

            item.cur = packet->data.input[i].cur.value / COM_RATE_CUR;
            item.cur_min = packet->data.input[i].cur.min / COM_RATE_CUR;
            item.cur_max = packet->data.input[i].cur.max / COM_RATE_CUR;

            insertItem(item);
            msleep(LOG_DELAY);
        }
    }
}
