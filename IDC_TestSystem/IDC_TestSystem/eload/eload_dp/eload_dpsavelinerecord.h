#ifndef ELOAD_DPSAVELINERECORD_H
#define ELOAD_DPSAVELINERECORD_H
#include "ELoad_dpsaveenv.h"
#include "dpcom/dpsaveline.h"
#include "ELoad_sql/ELoad_dblinerecords.h"

class ELoad_DpSaveLineRecord : public DpSaveLine
{
    Q_OBJECT
public:
    explicit ELoad_DpSaveLineRecord(QObject *parent = nullptr);

protected:
    virtual void saveLogItem(int id);
    void insertItem(DbLineRecordItem &item){ELoad_DbLineRecords::bulid()->insertItem(item);}
};

#endif // ELOAD_DPSAVELINERECORD_H
