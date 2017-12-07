/*
 * Si 实时数据日志保存线程
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_recordlogthread.h"
#include "si_sql/sidbrealrecords.h"

SI_RecordLogThread::SI_RecordLogThread(QObject *parent) : SI_ComLogThread(parent)
{

}


void SI_RecordLogThread::saveLogs()
{
    int row = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<row; ++i) {
        saveLogItem(i);
    }
}

void SI_RecordLogThread::saveLogItem(int id)
{
    SI_Rtu_Recv *packet = &(getPacket(id)->rtuData);
    if(packet->offLine > 0)
    {
        int line = packet->data.lineNum;
        for(int i=0; i<line; ++i)
        {
            SiDbRealRecordItem item;

            item.dev_id = id+1;
            item.line = i+1;
            item.sw = packet->data.sw[i];
            if(item.sw) {
                item.sw_str = tr("断开");
            } else  {
                item.sw_str = tr("闭合");
            }

            item.vol = packet->data.vol.value[i] / COM_RATE_VOL;
            item.cur = packet->data.cur.value[i] / COM_RATE_CUR;
            item.pow = packet->data.pow[i] / COM_RATE_POW;
            item.apow = packet->data.activePow[i] / COM_RATE_POW;
            item.pf = packet->data.pf[i] / COM_RATE_PF;
            item.ele = packet->data.ele[i] / COM_RATE_ELE;

            SiDbRealRecords::bulid()->insertItem(item);
        }
    }
}
