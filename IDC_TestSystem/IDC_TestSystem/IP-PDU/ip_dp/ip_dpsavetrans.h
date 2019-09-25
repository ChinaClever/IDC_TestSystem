#ifndef IP_DPSLAVETRANS_H
#define IP_DPSLAVETRANS_H

#include "ip_dpsaveenv.h"
#include "dpcom/dpsavetrans.h"
#include "ip_sql/ipdbmodbustrans.h"

class IP_DpSaveTrans : public DpSaveTrans
{
    Q_OBJECT
public:
    explicit IP_DpSaveTrans(QObject *parent = nullptr);

protected:
    void insertItem(DbModbusTransItem &item){IpDbModbusTrans::bulid()->insertItem(item);}
};

#endif // IP_DPSLAVETRANS_H
