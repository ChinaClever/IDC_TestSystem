#include "dpsaveoutput.h"

DpSaveOutput::DpSaveOutput(QObject *parent) : DpSaveRecord(parent)
{

}


void DpSaveOutput::saveLogItem(int id)
{
    sDataPacket *packet = &(mPackets->dev[id]);
    if(packet->offLine > 0)
    {
        int vol = packet->data.line[0].vol.value;
        int num = packet->data.outputNum;
        for(int i=0; i<num; ++i)
        {
            DbOutputItem item;

            item.dev_id = id;
            item.line = i+1;
            item.sw = packet->data.output[i].sw;
            if(item.sw) {
                item.sw_str = tr("断开");
            } else  {
                item.sw_str = tr("闭合");
            }

            item.vol = vol / COM_RATE_VOL;
            item.cur = packet->data.output[i].cur.value / COM_RATE_CUR;
            item.pow = packet->data.output[i].pow / COM_RATE_POW;
            item.apow = packet->data.output[i].activePow / COM_RATE_POW;
            item.pf = packet->data.output[i].pf / COM_RATE_PF;
            item.ele = packet->data.output[i].ele / COM_RATE_ELE;

            insertItem(item);
            msleep(LOG_DELAY);
        }
    }
}
