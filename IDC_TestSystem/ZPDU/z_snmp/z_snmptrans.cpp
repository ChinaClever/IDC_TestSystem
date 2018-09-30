#include "z_snmptrans.h"

Z_SnmpTrans::Z_SnmpTrans(QObject *parent) : SnmpThread(parent)
{
    mSnmpSend = new Z_SnmpSend;
    mSnmpRecv = new Z_SnmpRecv;
    mPackets = Z_DataPackets::bulid()->packets;
    mItem = Z_ConfigFile::bulid()->item;
}

Z_SnmpTrans *Z_SnmpTrans::bulid(QObject *parent)
{
    static Z_SnmpTrans* sington = NULL;
    if(sington == NULL) {
        sington = new Z_SnmpTrans(parent);
    }
    return sington;
}


void Z_SnmpTrans::workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
   mSnmpRecv->onResponseReceived(ip, oid, data);
}
