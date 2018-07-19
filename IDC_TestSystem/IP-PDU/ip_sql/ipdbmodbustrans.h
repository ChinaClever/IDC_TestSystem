#ifndef IPDBMODBUSTRANS_H
#define IPDBMODBUSTRANS_H
#include "si_sql/sidbmodbustrans.h"

#define IP_DB_ModbusTrans "ip_modbus_trans"
typedef SiDbModbusTransItem IpDbModbusTransItem;

class IpDbModbusTrans : public SiDbModbusTrans
{
    IpDbModbusTrans();
public:
    static IpDbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_ModbusTrans) ;}
};

#endif // IPDBMODBUSTRANS_H
