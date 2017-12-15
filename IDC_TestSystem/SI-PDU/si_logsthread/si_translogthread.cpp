/*
 * Si 传输日志保存线程
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_translogthread.h"
#include "si_sql/sidbmodbustrans.h"

SI_TransLogThread::SI_TransLogThread(QObject *parent) : SI_ComLogThread(parent)
{

}


void SI_TransLogThread::saveLogs()
{
    int row = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<row; ++i) {
        saveLogItem(i);
    }
}

void SI_TransLogThread::saveLogItem(int id)
{
    SiDbModbusTransItem item;

    item.dev_id = id+1;
    SiDevPacket *packet = getPacket(id);
    item.all_count = packet->count.count;
    item.ok_count = packet->count.okCount;
    item.err_count = packet->count.errCount;

    QString str =tr("离线");
    if(packet->rtuData.offLine)
        str =tr("在线");
    item.state = str;

    SiDbModbusTrans::bulid()->insertItem(item);
    msleep(LOG_DELAY);
}


