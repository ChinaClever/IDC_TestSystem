#ifndef MV1_DPSLAVETRANS_H
#define MV1_DPSLAVETRANS_H
#include "mv1_dpsavelinerecord.h"
#include "dpcom/dpsavetrans.h"
#include "mv1_sql/mv1_dbmodbustrans.h"

class MV1_DpSaveTrans : public DpSaveTrans
{
    Q_OBJECT
public:
    explicit MV1_DpSaveTrans(QObject *parent = nullptr);

protected:
    void insertItem(DbModbusTransItem &item){MV1_DbModbusTrans::bulid()->insertItem(item);}
};

#endif // MV1_DPSLAVETRANS_H
