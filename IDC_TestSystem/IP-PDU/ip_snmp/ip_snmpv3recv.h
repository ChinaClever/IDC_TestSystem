#ifndef IP_SNMPV3RECV_H
#define IP_SNMPV3RECV_H
#include "ip_snmpv1recv.h"

class IP_SnmpV3Recv
{
public:
    IP_SnmpV3Recv();
    void onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data);

protected:
    bool getMS(const QByteArray &oid);
    int getItemByOid(int id);
    void devData(const QByteArray &data);
    void devInfo(const QByteArray &data);

private:
    QString mIP, mOid;
    sDevPackets *mPackets;
    sDataPacket *mDataPacket;
};

#endif // IP_SNMPV3RECV_H
