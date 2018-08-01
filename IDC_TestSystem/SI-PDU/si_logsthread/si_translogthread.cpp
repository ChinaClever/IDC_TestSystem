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
    DbModbusTransItem item;

    item.dev_id = id+1;
    sDataPacket *packet = getPacket(id);

    item.all_count = packet->rtuCount.count;
    item.ok_count = packet->rtuCount.okCount;
    item.err_count = packet->rtuCount.errCount;

    QString str =tr("离线");
    if(packet->offLine)
        str =tr("在线");
    item.state = str;

    SiDbModbusTrans::bulid()->insertItem(item);
    msleep(LOG_DELAY);
}


