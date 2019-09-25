#ifndef IP_SNMPV1RECV_H
#define IP_SNMPV1RECV_H
#include "ip_snmpsend.h"

class IP_SnmpV1Recv
{
public:
    IP_SnmpV1Recv();
    void onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data);

protected:
    int getMS(const QByteArray &oid);
    int getItemByOid(int id);
    void devData(const QByteArray &data);
    void devInfo(const QByteArray &data);

private:
    QString mIP, mOid;
    sDevPackets *mPackets;
    sDataPacket *mDataPacket;
};

#endif // IP_SNMPV1RECV_H
