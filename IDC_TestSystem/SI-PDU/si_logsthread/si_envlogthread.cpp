/*
 * Si 环境日志保存线程
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_envlogthread.h"
#include "si_sql/sidbenv.h"

SI_EnvLogThread::SI_EnvLogThread(QObject *parent) : SI_ComLogThread(parent)
{

}


void SI_EnvLogThread::saveLogs()
{
    int row = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<row; ++i) {
        saveLogItem(i);
    }
}

void SI_EnvLogThread::saveLogItem(int id)
{
    SI_Rtu_Recv *packet = &(getPacket(id)->rtuData);
    if(packet->offLine > 0)
    {
        SiDbEnvItem item;

        item.dev_id = id+1;
        item.tem = packet->data.tem.value[0];
        item.tem_min = packet->data.tem.min[0];
        item.tem_max = packet->data.tem.max[0];
        item.hum = packet->data.hum.value[0];
        item.hum_min = packet->data.hum.min[0];
        item.hum_max = packet->data.hum.max[0];

        SiDbEnv::bulid()->insertItem(item);
    }

}
