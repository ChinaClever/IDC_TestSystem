#ifndef MV1_DPSLAVELINERECORD_H
#define MV1_DPSLAVELINERECORD_H
#include "mv1_dpsaveenv.h"
#include "dpcom/dpsaveline.h"
#include "mv1_sql/mv1_dblinerecords.h"

class MV1_DpSaveLineRecord : public DpSaveLine
{
    Q_OBJECT
public:
    explicit MV1_DpSaveLineRecord(QObject *parent = nullptr);

protected:
    void insertItem(DbLineRecordItem &item){MV1_DbLineRecords::bulid()->insertItem(item);}
};

#endif // MV1_DPSLAVELINERECORD_H
