#ifndef M_SNMPSEND_H
#define M_SNMPSEND_H
#include "snmp_zmrecv.h"

#define M_MIB_OID "8"
//#define M_MIB_OID "7"

class M_SnmpSend
{
public:
    M_SnmpSend();
    int requestSubOid(int id, QStringList &oid);

private:
};

#endif // M_SNMPSEND_H
