#ifndef R_DPSAVELINERECORD_H
#define R_DPSAVELINERECORD_H
#include "r_dpsaveenv.h"
#include "dpcom/dpsaveline.h"
#include "r_sql/r_dblinerecords.h"

class R_DpSaveLineRecord : public DpSaveLine
{
    Q_OBJECT
public:
    explicit R_DpSaveLineRecord(QObject *parent = nullptr);

protected:
    void insertItem(DbLineRecordItem &item){R_DbLineRecords::bulid()->insertItem(item);}
};

#endif // R_DPSAVELINERECORD_H
