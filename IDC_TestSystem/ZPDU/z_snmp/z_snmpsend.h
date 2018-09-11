#ifndef Z_SNMPSEND_H
#define Z_SNMPSEND_H
#include "snmp.h"

#define Z_MIB_OID ".7"

class Z_SnmpSend
{
public:
    Z_SnmpSend();
    QString requestSubOid() { return QString(MIB_OID_CLEVER) + Z_MIB_OID; }

private:
};

#endif // Z_SNMPSEND_H
