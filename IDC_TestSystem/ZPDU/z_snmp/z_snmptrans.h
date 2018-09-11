#ifndef Z_SNMPTRANS_H
#define Z_SNMPTRANS_H

#include "z_snmprecv.h"

class Z_SnmpTrans : public Snmp
{
    Q_OBJECT
public:
    explicit Z_SnmpTrans(QObject *parent = nullptr);
    static Z_SnmpTrans *bulid(QObject *parent = nullptr);

signals:

protected slots:
    void initFunSLot();
    void workDown(const QString &ip, const QByteArray &oid, const QByteArray &data);

private:
    Z_SnmpSend *mSnmpSend;
    Z_SnmpRecv *mSnmpRecv;
};

#endif // Z_SNMPTRANS_H
