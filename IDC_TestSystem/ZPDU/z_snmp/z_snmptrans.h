#ifndef Z_SNMPTRANS_H
#define Z_SNMPTRANS_H

#include "z_snmprecv.h"
#include "z_com/z_datapackets.h"

class Z_SnmpTrans : public SnmpThread
{
    Q_OBJECT
public:
    explicit Z_SnmpTrans(QObject *parent = nullptr);
    static Z_SnmpTrans *bulid(QObject *parent = nullptr);

signals:

protected:
    QStringList getRequestValues(int id){QStringList list; return list;}
    int getRequestSubValues(int id, QStringList &oid) { return mSnmpSend->requestSubOid(id, oid);}
    void workDown(const QString &ip, const QByteArray &oid, const QByteArray &data);

private:
    Z_SnmpSend *mSnmpSend;
    Z_SnmpRecv *mSnmpRecv;
};

#endif // Z_SNMPTRANS_H
