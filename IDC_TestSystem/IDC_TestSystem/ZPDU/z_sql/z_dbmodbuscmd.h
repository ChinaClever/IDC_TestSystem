#ifndef Z_DBMODBUSCMD_H
#define Z_DBMODBUSCMD_H
#include "sqlcom/dbmodbuscmd.h"

#define Z_DB_ModbusCmd "z_modbus_cmd"

class Z_DbModbusCmd : public DbModbusCmd
{
    Z_DbModbusCmd();
public:
    static Z_DbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(Z_DB_ModbusCmd) ;}
};

#endif // Z_DBMODBUSCMD_H
