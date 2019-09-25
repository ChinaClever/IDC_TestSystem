#ifndef Z_SNMPSEND_H
#define Z_SNMPSEND_H
#include "snmp_zmrecv.h"

#define Z_MIB_OID "7"

class Z_SnmpSend
{
public:
    Z_SnmpSend();
    int requestSubOid(int id, QStringList &oid);

private:
};

#endif // Z_SNMPSEND_H
