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
    sDataPacket *packet = getPacket(id);
    if(packet->offLine > 0)
    {
        DbEnvItem item;

        item.dev_id = id+1;
        item.tem = packet->data.env.tem[0].value;
        item.tem_min = packet->data.env.tem[0].min;
        item.tem_max = packet->data.env.tem[0].max;
        item.hum = packet->data.env.hum[0].value;
        item.hum_min = packet->data.env.hum[0].min;
        item.hum_max = packet->data.env.hum[0].max;

        SiDbEnv::bulid()->insertItem(item);
        msleep(LOG_DELAY);
    }

}
