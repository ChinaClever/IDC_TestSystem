#include "z_snmpsend.h"

Z_SnmpSend::Z_SnmpSend()
{

}

int Z_SnmpSend::requestSubOid(int id, QStringList &oid)
{
    QString str = QString("%1.%2.%3").arg(MIB_OID_CLEVER).arg(Z_MIB_OID).arg(id);
    oid << str;

    return str.size();
}
