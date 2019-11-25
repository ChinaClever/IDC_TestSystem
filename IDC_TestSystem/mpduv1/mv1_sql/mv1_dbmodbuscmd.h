#ifndef MV1_DBMODBUSCMD_H
#define MV1_DBMODBUSCMD_H
#include "sqlcom/dbmodbuscmd.h"

#define MV1_DB_ModbusCmd "MV1_modbus_cmd"

class MV1_DbModbusCmd : public DbModbusCmd
{
    MV1_DbModbusCmd();
public:
    static MV1_DbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(MV1_DB_ModbusCmd) ;}
};

#endif // MV1_DBMODBUSCMD_H
