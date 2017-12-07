/*
 * Si 设备阈值日志保存线程
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_thresholdlogthread.h"
#include "si_sql/sidbthresholds.h"

SI_ThresholdLogThread::SI_ThresholdLogThread(QObject *parent) : SI_ComLogThread(parent)
{

}

void SI_ThresholdLogThread::saveLogs()
{
    int row = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<row; ++i) {
        saveLogItem(i);
    }
}

void SI_ThresholdLogThread::saveLogItem(int id)
{
    SI_Rtu_Recv *packet = &(getPacket(id)->rtuData);
    if(packet->offLine > 0)
    {
        int line = packet->data.lineNum;
        for(int i=0; i<line; ++i)
        {
            SiDbThresholdItem item;

            item.dev_id = id+1;
            item.line = i+1;
            item.vol = packet->data.vol.value[i] / COM_RATE_VOL;
            item.vol_min = packet->data.vol.min[i] / COM_RATE_VOL;
            item.vol_max = packet->data.vol.max[i] / COM_RATE_VOL;

            item.cur = packet->data.cur.value[i] / COM_RATE_CUR;
            item.cur_min = packet->data.cur.min[i] / COM_RATE_CUR;
            item.cur_max = packet->data.cur.max[i] / COM_RATE_CUR;

            SiDbThresholds::bulid()->insertItem(item);
        }
    }
}
