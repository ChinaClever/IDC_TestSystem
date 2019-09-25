#ifndef M_DPSLAVETRANS_H
#define M_DPSLAVETRANS_H
#include "m_dpsavelinerecord.h"
#include "dpcom/dpsavetrans.h"
#include "m_sql/m_dbmodbustrans.h"

class M_DpSaveTrans : public DpSaveTrans
{
    Q_OBJECT
public:
    explicit M_DpSaveTrans(QObject *parent = nullptr);

protected:
    void insertItem(DbModbusTransItem &item){M_DbModbusTrans::bulid()->insertItem(item);}
};

#endif // M_DPSLAVETRANS_H
