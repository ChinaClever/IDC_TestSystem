/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_snmpsend.h"

MV1_SnmpSend::MV1_SnmpSend()
{

}

int MV1_SnmpSend::requestSubOid(int id, QStringList &oid)
{
    QString str = QString("%1.%2.%3").arg(MIB_OID_CLEVER).arg(MV1_MIB_OID).arg(id);
    oid << str;

    return oid.size();
}
