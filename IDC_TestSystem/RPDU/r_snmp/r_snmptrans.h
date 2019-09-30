#ifndef R_SNMPTRANS_H
#define R_SNMPTRANS_H

#include "r_snmprecv.h"

class R_SnmpTrans : public SnmpThread
{
    Q_OBJECT
    explicit R_SnmpTrans(QObject *parent = nullptr);
public:
    static R_SnmpTrans *bulid(QObject *parent = nullptr);

signals:

protected:
    QStringList getRequestValues(int){QStringList list; return list;}
    int getRequestSubValues(int id, QStringList &oid) { return mSnmpSend->requestSubOid(id, oid);}
    void workDown(const QString &ip, const QByteArray &oid, const QByteArray &data);
    virtual int getDelay() {return 2000;}

private:
    R_SnmpSend *mSnmpSend;
    R_SnmpRecv *mSnmpRecv;
};

#endif // R_SNMPTRANS_H
