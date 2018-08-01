#ifndef SIDBMODBUSCMD_H
#define SIDBMODBUSCMD_H

#include "sqlcom/dbmodbuscmd.h"

#define SI_DB_ModbusCmd "si_modbus_cmd"

class SiDbModbusCmd : public DbModbusCmd
{
    SiDbModbusCmd();
public:
    static SiDbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_ModbusCmd) ;}    
};

#endif // SIDBMODBUSCMD_H
