#include "r_snmpsend.h"

R_SnmpSend::R_SnmpSend()
{

}

int R_SnmpSend::requestSubOid(int id, QStringList &oid)
{
    QString str = QString("%1.%2.%3").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(id);
    oid << str;
    return oid.size();
}
