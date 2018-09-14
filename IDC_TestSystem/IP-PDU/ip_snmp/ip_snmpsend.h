#ifndef IP_SNMPSEND_H
#define IP_SNMPSEND_H
#include "snmp_zmrecv.h"
#include "ip_com/ipdatapackets.h"

#define IP_MIB_OID "10.3"

class IP_SnmpSend
{
public:
    IP_SnmpSend();    

    QStringList requestValues(int id);
    int requestSubOid(int id, QStringList &oid);
};

#endif // IP_SNMPSEND_H
