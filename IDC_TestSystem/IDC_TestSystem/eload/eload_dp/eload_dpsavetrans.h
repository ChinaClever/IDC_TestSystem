#ifndef ELOAD_DPSAVETRANS_H
#define ELOAD_DPSAVETRANS_H
#include "eload_dpsavelinethreshold.h"
#include "dpcom/dpsavetrans.h"
#include "ELoad_sql/ELoad_dbmodbustrans.h"

class ELoad_DpSaveTrans : public DpSaveTrans
{
    Q_OBJECT
public:
    explicit ELoad_DpSaveTrans(QObject *parent = nullptr);

protected:
    void insertItem(DbModbusTransItem &item){ELoad_DbModbusTrans::bulid()->insertItem(item);}
};


#endif // ELOAD_DPSAVETRANS_H
