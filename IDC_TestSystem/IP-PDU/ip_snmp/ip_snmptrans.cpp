#include "ip_snmptrans.h"

IP_SnmpTrans::IP_SnmpTrans(QObject *parent) : SnmpThread(parent)
{
    mSnmpSend = new IP_SnmpSend;
    mSnmpRecv = new IP_SnmpRecv;
    mPackets = IpDataPackets::bulid()->packets;
}

//IP_SnmpTrans *IP_SnmpTrans::bulid(QObject *parent)
//{
//    static IP_SnmpTrans* sington = NULL;
//    if(sington == NULL) {
//        sington = new IP_SnmpTrans(parent);
//    }
//    return sington;
//}


//void IP_SnmpTrans::workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)
//{
//   mSnmpRecv->onResponseReceived(ip, oid, data);
//}

