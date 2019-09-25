#ifndef M_DBMODBUSTRANS_H
#define M_DBMODBUSTRANS_H
#include "sqlcom/dbmodbustrans.h"

#define M_DB_ModbusTrans "m_modbus_trans"

class M_DbModbusTrans : public DbModbusTrans
{
    M_DbModbusTrans();
public:
    static M_DbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(M_DB_ModbusTrans) ;}
};

#endif // M_DBMODBUSTRANS_H
