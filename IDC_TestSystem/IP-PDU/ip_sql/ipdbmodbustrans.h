#ifndef IPDBMODBUSTRANS_H
#define IPDBMODBUSTRANS_H
#include "sqlcom/dbmodbustrans.h"

#define IP_DB_ModbusTrans "ip_modbus_trans"

class IpDbModbusTrans : public DbModbusTrans
{
    IpDbModbusTrans();
public:
    static IpDbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_ModbusTrans) ;}
};

#endif // IPDBMODBUSTRANS_H
