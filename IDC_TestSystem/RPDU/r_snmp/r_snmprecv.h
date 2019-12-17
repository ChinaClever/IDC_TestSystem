#ifndef R_SNMPRECV_H
#define R_SNMPRECV_H
#include "r_snmpsend.h"
#include "r_com/r_datapackets.h"

class R_SnmpRecv:public SNMP_ZmRecv
{
public:
    R_SnmpRecv();

    void onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data);
protected:
    void devTypeData(int value, sDataPacket *pkt);
    void getBreakerManagerOPNum(sObjData *obj,const QByteArray &data){}
    void devInfo(const QByteArray &data);
    void lineData(const QByteArray &data);
    void envData(const QByteArray &data);
    void outputInfo(const QByteArray &data);
    void envMinData(const QByteArray &data);
    void envMaxData(const QByteArray &data);
};

#endif // R_SNMPRECV_H
