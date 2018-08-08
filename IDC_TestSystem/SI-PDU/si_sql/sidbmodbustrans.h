#ifndef SIDBMODBUSTRANS_H
#define SIDBMODBUSTRANS_H

#include "sqlcom/dbmodbustrans.h"

#define SI_DB_ModbusTrans "si_modbus_trans"

class SiDbModbusTrans : public DbModbusTrans
{
    SiDbModbusTrans();
public:
    static SiDbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_ModbusTrans) ;}    
};

#endif // SIDBMODBUSTRANS_H
