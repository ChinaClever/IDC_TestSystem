#ifndef MV1_SNMPSEND_H
#define MV1_SNMPSEND_H
#include "snmp_zmrecv.h"

#define MV1_MIB_OID "10.8"

class MV1_SnmpSend
{
public:
    MV1_SnmpSend();
    int requestSubOid(int id, QStringList &oid);

private:
};

#endif // MV1_SNMPSEND_H
