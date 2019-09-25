#ifndef ELOAD_DBMODBUSTRANS_H
#define ELOAD_DBMODBUSTRANS_H
#include "sqlcom/dbmodbustrans.h"

#define ELoad_DB_ModbusTrans "eload_modbus_trans"

class ELoad_DbModbusTrans : public DbModbusTrans
{
    ELoad_DbModbusTrans();
public:
    static ELoad_DbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(ELoad_DB_ModbusTrans) ;}
};

#endif // ELOAD_DBMODBUSTRANS_H
