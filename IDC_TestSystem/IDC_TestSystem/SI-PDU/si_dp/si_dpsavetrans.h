#ifndef SI_DPSLAVETRANS_H
#define SI_DPSLAVETRANS_H

#include "si_dpsaverecord.h"
#include "dpcom/dpsavetrans.h"
#include "si_sql/sidbmodbustrans.h"

class SI_DpSaveTrans : public DpSaveTrans
{
    Q_OBJECT
public:
    explicit SI_DpSaveTrans(QObject *parent = nullptr);

protected:
    void insertItem(DbModbusTransItem &item){SiDbModbusTrans::bulid()->insertItem(item);}
};

#endif // SI_DPSLAVETRANS_H
