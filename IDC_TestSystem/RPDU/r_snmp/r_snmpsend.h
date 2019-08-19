#ifndef R_SNMPSEND_H
#define R_SNMPSEND_H
#include "snmp_zmrecv.h"
#include "r_snmprecv.h"

#define R_MIB_OID "6"

class R_SnmpSend
{
public:
    R_SnmpSend();
    int requestSubOid(int id, QStringList &oid);

private:
};

#endif // R_SNMPSEND_H
