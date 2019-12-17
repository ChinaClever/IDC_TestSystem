#ifndef M_SNMPRECV_H
#define M_SNMPRECV_H
#include "m_snmpsend.h"
#include "m_com/m_datapackets.h"

class M_SnmpRecv : public SNMP_ZmRecv
{
public:
    M_SnmpRecv();

protected:
    void devTypeData(int value, sDataPacket *pkt);
    void getBreakerManagerOPNum(sObjData *obj,const QByteArray &data);
};

#endif // M_SNMPRECV_H
