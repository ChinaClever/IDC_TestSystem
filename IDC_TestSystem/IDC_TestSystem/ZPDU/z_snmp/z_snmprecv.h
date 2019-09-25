#ifndef Z_SNMPRECV_H
#define Z_SNMPRECV_H
#include "z_snmpsend.h"
#include "z_com/z_datapackets.h"

class Z_SnmpRecv : public SNMP_ZmRecv
{
public:
    Z_SnmpRecv();

protected:
    void devTypeData(int value, sDataPacket *pkt);
    void lineData(const QByteArray &data);
};

#endif // Z_SNMPRECV_H
