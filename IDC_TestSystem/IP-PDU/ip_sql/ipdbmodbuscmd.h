#ifndef IPDBMODBUSCMD_H
#define IPDBMODBUSCMD_H
#include "si_sql/sidbmodbuscmd.h"

#define IP_DB_ModbusCmd "ip_modbus_cmd"
typedef SiDbModbusCmdItem IpDbModbusCmdItem;

class IpDbModbusCmd : public SiDbModbusCmd
{
    IpDbModbusCmd();
public:
    static IpDbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_ModbusCmd) ;}

};

#endif // IPDBMODBUSCMD_H
