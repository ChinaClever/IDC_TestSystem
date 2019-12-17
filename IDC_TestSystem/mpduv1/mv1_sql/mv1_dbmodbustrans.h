#ifndef MV1_DBMODBUSTRANS_H
#define MV1_DBMODBUSTRANS_H
#include "sqlcom/dbmodbustrans.h"

#define MV1_DB_ModbusTrans "mv1_modbus_trans"

class MV1_DbModbusTrans : public DbModbusTrans
{
    MV1_DbModbusTrans();
public:
    static MV1_DbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(MV1_DB_ModbusTrans) ;}
};

#endif // MV1_DBMODBUSTRANS_H
