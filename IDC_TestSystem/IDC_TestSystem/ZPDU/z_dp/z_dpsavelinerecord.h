#ifndef Z_DPSAVELINERECORD_H
#define Z_DPSAVELINERECORD_H
#include "z_dpsaveenv.h"
#include "dpcom/dpsaveline.h"
#include "z_sql/z_dblinerecords.h"

class Z_DpSaveLineRecord : public DpSaveLine
{
    Q_OBJECT
public:
    explicit Z_DpSaveLineRecord(QObject *parent = nullptr);

protected:
    void insertItem(DbLineRecordItem &item){Z_DbLineRecords::bulid()->insertItem(item);}
};

#endif // Z_DPSAVELINERECORD_H
