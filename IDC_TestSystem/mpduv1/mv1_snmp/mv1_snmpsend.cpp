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
    int start = 0,end = 0;
    switch(id)
    {
    case 1:start = 1 ; end = 9;break;
    case 2:start = 9 ; end = 16;break;
    case 3:start = 16 ; end = 23;break;
    case 4:start = 23 ; end = 30;break;
    default:
        start = 1 ; end = 9;break;
    }

    for(int i = start ; i < end ; i++)
    {
        QString str = QString("%1.%2.%3").arg(MIB_OID_CLEVER).arg(MV1_MIB_OID).arg(i);
        oid << str;
    }

    return oid.size();
}
