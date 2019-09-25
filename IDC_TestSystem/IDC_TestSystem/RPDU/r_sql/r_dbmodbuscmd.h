#ifndef R_DBMODBUSCMD_H
#define R_DBMODBUSCMD_H
#include "sqlcom/dbmodbuscmd.h"

#define R_DB_ModbusCmd "r_modbus_cmd"

class R_DbModbusCmd : public DbModbusCmd
{
    R_DbModbusCmd();
public:
    static R_DbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(R_DB_ModbusCmd) ;}
};

#endif // R_DBMODBUSCMD_H
