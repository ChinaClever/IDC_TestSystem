/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_snmptrans.h"

MV1_SnmpTrans::MV1_SnmpTrans(QObject *parent) : SnmpThread(parent)
{
    mSnmpSend = new MV1_SnmpSend;
    mSnmpRecv = new MV1_SnmpRecv;
    mPackets = MV1_DataPackets::bulid()->packets;
    mItem = MV1_ConfigFile::bulid()->item;
}

MV1_SnmpTrans *MV1_SnmpTrans::bulid(QObject *parent)
{
    static MV1_SnmpTrans* sington = NULL;
    if(sington == NULL) {
        sington = new MV1_SnmpTrans(parent);
    }
    return sington;
}


void MV1_SnmpTrans::workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
   mSnmpRecv->onResponseReceived(ip, oid, data);
}
