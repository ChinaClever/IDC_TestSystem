#ifndef M_SNMPTRANS_H
#define M_SNMPTRANS_H

#include "m_snmprecv.h"

class M_SnmpTrans : public SnmpThread
{
    Q_OBJECT
    explicit M_SnmpTrans(QObject *parent = nullptr);
public:
    static M_SnmpTrans *bulid(QObject *parent = nullptr);

signals:

protected:
    QStringList getRequestValues(int){QStringList list; return list;}
    int getRequestSubValues(int id, QStringList &oid) { return mSnmpSend->requestSubOid(id, oid);}
    void workDown(const QString &ip, const QByteArray &oid, const QByteArray &data);

private:
    M_SnmpSend *mSnmpSend;
    M_SnmpRecv *mSnmpRecv;
};

#endif // M_SNMPTRANS_H
