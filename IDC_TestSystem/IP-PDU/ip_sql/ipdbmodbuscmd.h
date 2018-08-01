#ifndef IPDBMODBUSCMD_H
#define IPDBMODBUSCMD_H
#include "sqlcom/dbmodbuscmd.h"

#define IP_DB_ModbusCmd "ip_modbus_cmd"

class IpDbModbusCmd : public DbModbusCmd
{
    IpDbModbusCmd();
public:
    static IpDbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_ModbusCmd) ;}
};

#endif // IPDBMODBUSCMD_H
