#ifndef MV1_SNMPTRANS_H
#define MV1_SNMPTRANS_H

#include "mv1_snmprecv.h"

class MV1_SnmpTrans : public SnmpThread
{
    Q_OBJECT
    explicit MV1_SnmpTrans(QObject *parent = nullptr);
public:
    static MV1_SnmpTrans *bulid(QObject *parent = nullptr);

signals:

protected:
    QStringList getRequestValues(int){QStringList list; return list;}
    int getRequestSubValues(int id, QStringList &oid) { return mSnmpSend->requestSubOid(id, oid);}
    void workDown(const QString &ip, const QByteArray &oid, const QByteArray &data);
    virtual int getDelay() {return 2000;}//400

private:
    MV1_SnmpSend *mSnmpSend;
    MV1_SnmpRecv *mSnmpRecv;
};

#endif // MV1_SNMPTRANS_H
