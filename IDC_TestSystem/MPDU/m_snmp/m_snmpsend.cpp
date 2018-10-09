/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_snmpsend.h"

M_SnmpSend::M_SnmpSend()
{

}

int M_SnmpSend::requestSubOid(int id, QStringList &oid)
{
    QString str = QString("%1.%2.%3").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(id);
    oid << str;

    return oid.size();
}
