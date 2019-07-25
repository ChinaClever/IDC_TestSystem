#include "r_snmptrans.h"

R_SnmpTrans::R_SnmpTrans(QObject *parent) : SnmpThread(parent)
{
    mSnmpSend = new R_SnmpSend;
    mSnmpRecv = new R_SnmpRecv;
    mPackets = R_DataPackets::bulid()->packets;
    mItem = R_ConfigFile::bulid()->item;
}

R_SnmpTrans *R_SnmpTrans::bulid(QObject *parent)
{
    static R_SnmpTrans* sington = NULL;
    if(sington == NULL) {
        sington = new R_SnmpTrans(parent);
    }
    return sington;
}


void R_SnmpTrans::workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
   mSnmpRecv->onResponseReceived(ip, oid, data);
}
