#include "ip_snmpsend.h"

IP_SnmpSend::IP_SnmpSend()
{

}

QStringList IP_SnmpSend::requestValues(int id)
{
    QStringList list;

    return list;
}


int IP_SnmpSend::requestSubOid(int id, QStringList &oid)
{
    sConfigItem *item = IP_ConfigFile::bulid()->item;
    if(item->v) {
        if(id==1) oid << QString("%1.%2.%3").arg(MIB_OID_CLEVER).arg(IP_MIB_OID).arg(id);
        oid << QString("%1.%2.%3").arg(MIB_OID_CLEVER).arg(IP_MIB_OID).arg(id+1); //.arg(id);
    } else {
        int end = 11*id, start = end-10;
        if(id == 1) oid << QString("%1.%2.1.%3").arg(MIB_OID_CLEVER).arg(IP_MIB_OID).arg(id);
        for(int i=start; i<= end; i++) {
            oid << QString("%1.%2.2.%3").arg(MIB_OID_CLEVER).arg(IP_MIB_OID).arg(i);
        }
    }

    return oid.size();
}
