#ifndef MV1_SNMPRECV_H
#define MV1_SNMPRECV_H
#include "mv1_snmpsend.h"
#include "mv1_com/mv1_datapackets.h"

class MV1_SnmpRecv : public SNMP_ZmRecv
{
public:
    MV1_SnmpRecv();
    void onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data);
protected:
    void getMS(const QByteArray &oid);
    void devTypeData(int value, sDataPacket *pkt);
    void getBreakerManagerOPNum(sObjData *obj,const QByteArray &data);
    void devInfo(const QByteArray &data);
    void lineData(const QByteArray &data);
    void envData(const QByteArray &data);
    void outputInfo(const QByteArray &data);
private:
    QMap<int,int> mcountLoopNum;
};

#endif // MV1_SNMPRECV_H
