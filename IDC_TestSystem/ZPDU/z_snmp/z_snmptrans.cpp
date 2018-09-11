#include "z_snmptrans.h"

Z_SnmpTrans::Z_SnmpTrans(QObject *parent) : Snmp(parent)
{
    mSnmpSend = new Z_SnmpSend;
    mSnmpRecv = new Z_SnmpRecv;

    QTimer::singleShot(50,this,SLOT(initFunSLot())); //延时初始化
}

Z_SnmpTrans *Z_SnmpTrans::bulid(QObject *parent)
{
    static Z_SnmpTrans* sington = NULL;
    if(sington == NULL) {
        sington = new Z_SnmpTrans(parent);
    }
    return sington;
}

void Z_SnmpTrans::initFunSLot()
{
    QString oid = mSnmpSend->requestSubOid();
    requestSubValues(oid);
}

void Z_SnmpTrans::workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
   mSnmpRecv->onResponseReceived(ip, oid, data);
}
