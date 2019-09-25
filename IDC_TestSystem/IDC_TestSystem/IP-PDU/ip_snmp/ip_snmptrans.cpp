#include "ip_snmptrans.h"

IP_SnmpTrans::IP_SnmpTrans(QObject *parent) : SnmpThread(parent)
{
    mSnmpSend = new IP_SnmpSend;
    mSnmpV1Recv = new IP_SnmpV1Recv ;
    mSnmpV3Recv = new IP_SnmpV3Recv ;
    mPackets = IpDataPackets::bulid()->packets;
    mItem = IP_ConfigFile::bulid()->item;
}

IP_SnmpTrans *IP_SnmpTrans::bulid(QObject *parent)
{
    static IP_SnmpTrans* sington = NULL;
    if(sington == NULL) {
        sington = new IP_SnmpTrans(parent);
    }
    return sington;
}


void IP_SnmpTrans::workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
    sConfigItem *item = IP_ConfigFile::bulid()->item;
    if(item->v) {
        mSnmpV3Recv->onResponseReceived(ip, oid, data);
    } else {
        mSnmpV1Recv->onResponseReceived(ip, oid, data);
    }

}

