#include "dpsavetrans.h"
#include "sqlcom/dbmodbustrans.h"

DpSaveTrans::DpSaveTrans(QObject *parent) : DpSaveRecord(parent)
{

}


void DpSaveTrans::saveLogItem(int id)
{
    DbModbusTransItem item;

    sDataPacket *dev = &(mPackets->dev[id]);
    sRtuCount *packet = &(dev->rtuCount);

    item.dev_id = id;
    item.all_count = packet->count;
    item.ok_count = packet->okCount;
    item.err_count = packet->errCount;

    QString str =tr("离线");
    if(dev->offLine)
        str =tr("在线");
    item.state = str;

    insertItem(item);
    msleep(LOG_DELAY);
}
