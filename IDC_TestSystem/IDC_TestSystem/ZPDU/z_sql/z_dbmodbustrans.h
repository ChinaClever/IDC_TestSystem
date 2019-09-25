#ifndef Z_DBMODBUSTRANS_H
#define Z_DBMODBUSTRANS_H
#include "sqlcom/dbmodbustrans.h"

#define Z_DB_ModbusTrans "z_modbus_trans"

class Z_DbModbusTrans : public DbModbusTrans
{
    Z_DbModbusTrans();
public:
    static Z_DbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(Z_DB_ModbusTrans) ;}
};

#endif // Z_DBMODBUSTRANS_H
