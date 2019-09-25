#ifndef R_DBMODBUSTRANS_H
#define R_DBMODBUSTRANS_H
#include "sqlcom/dbmodbustrans.h"

#define R_DB_ModbusTrans "r_modbus_trans"

class R_DbModbusTrans : public DbModbusTrans
{
    R_DbModbusTrans();
public:
    static R_DbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(R_DB_ModbusTrans) ;}
};

#endif // R_DBMODBUSTRANS_H
