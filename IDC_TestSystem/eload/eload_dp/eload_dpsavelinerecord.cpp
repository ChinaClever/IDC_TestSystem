#include "eload_dpsavelinerecord.h"

ELoad_DpSaveLineRecord::ELoad_DpSaveLineRecord(QObject *parent) : DpSaveLine(parent)
{

}


void ELoad_DpSaveLineRecord::saveLogItem(int id)
{
    sDataPacket *packet = &(mPackets->dev[id]);
    if(packet->offLine > 0)
    {
        int line = packet->data.inputNum;
        for(int i=0; i<line; ++i)
        {
            DbLineRecordItem item;

            item.dev_id = id;
            item.line = i+1;
            item.sw = packet->data.input[i].sw;
            item.sw_str = tr("断开");
            if(item.sw == mSwValue) {
                item.sw_str = tr("闭合");
            }

            item.vol = packet->data.input[i].vol.value / COM_RATE_VOL;
            item.cur = packet->data.input[i].cur.value / COM_RATE_CUR2;
            item.pow = packet->data.input[i].pow / COM_RATE_POW;
            item.apow = packet->data.input[i].activePow / COM_RATE_POW;
            item.pf = packet->data.input[i].pf / COM_RATE_PF;
            item.ele = packet->data.input[i].ele / COM_RATE_ELE;

            insertItem(item);
            msleep(LOG_DELAY);
        }
    }
}
