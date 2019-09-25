#ifndef SI_DPSAVERECORD_H
#define SI_DPSAVERECORD_H

#include "si_dpsaveenv.h"
#include "dpcom/dpsaveline.h"
#include "si_sql/sidbrealrecords.h"

class SI_DpSaveRecord : public DpSaveLine
{
    Q_OBJECT
public:
    explicit SI_DpSaveRecord(QObject *parent = nullptr);

protected:
    void insertItem(DbLineRecordItem &item){SiDbRealRecords::bulid()->insertItem(item);}
};

#endif // SI_DPSAVERECORD_H
