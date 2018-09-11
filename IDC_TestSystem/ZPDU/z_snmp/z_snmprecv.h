#ifndef Z_SNMPRECV_H
#define Z_SNMPRECV_H
#include "z_snmpsend.h"
#include "z_com/z_datapackets.h"

class Z_SnmpRecv
{
public:
    Z_SnmpRecv();

    void onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data);

protected:
    int getItemByOid(int id);
    void getMS(const QByteArray &oid);
    void devInfo(const QByteArray &data);
    void devTypeData(int value, sDataPacket *pkt);

    void lineData(const QByteArray &data);
    void loopData(const QByteArray &data);
    void envData(const QByteArray &data);
    void outputCur(const QByteArray &data);
    void outputData(const QByteArray &data);

private:
    QString mIP, mOid;
    sDataPacket *mDataPacket;
};

#endif // Z_SNMPRECV_H
