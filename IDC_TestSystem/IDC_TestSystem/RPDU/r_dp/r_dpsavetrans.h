#ifndef R_DPSAVETRANS_H
#define R_DPSAVETRANS_H
#include "r_dpsaveloop.h"
#include "dpcom/dpsavetrans.h"
#include "r_sql/r_dbmodbustrans.h"

class R_DpSaveTrans : public DpSaveTrans
{
    Q_OBJECT
public:
    explicit R_DpSaveTrans(QObject *parent = nullptr);

protected:
    void insertItem(DbModbusTransItem &item){R_DbModbusTrans::bulid()->insertItem(item);}
};

#endif // R_DPSAVETRANS_H
