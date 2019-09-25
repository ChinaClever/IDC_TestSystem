#ifndef Z_DPSAVETRANS_H
#define Z_DPSAVETRANS_H
#include "z_dpsaveloop.h"
#include "dpcom/dpsavetrans.h"
#include "z_sql/z_dbmodbustrans.h"

class Z_DpSaveTrans : public DpSaveTrans
{
    Q_OBJECT
public:
    explicit Z_DpSaveTrans(QObject *parent = nullptr);

protected:
    void insertItem(DbModbusTransItem &item){Z_DbModbusTrans::bulid()->insertItem(item);}
};

#endif // Z_DPSAVETRANS_H
