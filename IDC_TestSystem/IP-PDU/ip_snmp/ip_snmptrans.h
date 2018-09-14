#ifndef IP_SNMPTRANS_H
#define IP_SNMPTRANS_H

#include "ip_snmpv3recv.h"

class IP_SnmpTrans : public SnmpThread
{
    Q_OBJECT
public:
    explicit IP_SnmpTrans(QObject *parent = nullptr);
    static IP_SnmpTrans *bulid(QObject *parent = nullptr);

signals:

protected:
    QStringList getRequestValues(int id){return mSnmpSend->requestValues(id);}
    int getRequestSubValues(int id, QStringList &oid) { return mSnmpSend->requestSubOid(id, oid);}
    void workDown(const QString &ip, const QByteArray &oid, const QByteArray &data);

private:
    IP_SnmpSend *mSnmpSend;
    IP_SnmpV1Recv *mSnmpV1Recv;
    IP_SnmpV3Recv *mSnmpV3Recv;
};

#endif // IP_SNMPTRANS_H
