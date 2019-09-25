#ifndef M_DBMODBUSCMD_H
#define M_DBMODBUSCMD_H
#include "sqlcom/dbmodbuscmd.h"

#define M_DB_ModbusCmd "M_modbus_cmd"

class M_DbModbusCmd : public DbModbusCmd
{
    M_DbModbusCmd();
public:
    static M_DbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(M_DB_ModbusCmd) ;}
};

#endif // M_DBMODBUSCMD_H
