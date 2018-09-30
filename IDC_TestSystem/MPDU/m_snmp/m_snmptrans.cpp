/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_snmptrans.h"

M_SnmpTrans::M_SnmpTrans(QObject *parent) : SnmpThread(parent)
{
    mSnmpSend = new M_SnmpSend;
    mSnmpRecv = new M_SnmpRecv;
    mPackets = M_DataPackets::bulid()->packets;
    mItem = M_ConfigFile::bulid()->item;
}

M_SnmpTrans *M_SnmpTrans::bulid(QObject *parent)
{
    static M_SnmpTrans* sington = NULL;
    if(sington == NULL) {
        sington = new M_SnmpTrans(parent);
    }
    return sington;
}


void M_SnmpTrans::workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
   mSnmpRecv->onResponseReceived(ip, oid, data);
}
