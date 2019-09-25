#ifndef ELOAD_DBMODBUSCMD_H
#define ELOAD_DBMODBUSCMD_H
#include "sqlcom/dbmodbuscmd.h"

#define ELoad_DB_ModbusCmd "eload_modbus_cmd"

class ELoad_DbModbusCmd : public DbModbusCmd
{
    ELoad_DbModbusCmd();
public:
    static ELoad_DbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(ELoad_DB_ModbusCmd) ;}
};

#endif // ELOAD_DBMODBUSCMD_H
