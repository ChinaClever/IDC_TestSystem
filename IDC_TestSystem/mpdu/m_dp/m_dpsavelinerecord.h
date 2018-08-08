#ifndef M_DPSLAVELINERECORD_H
#define M_DPSLAVELINERECORD_H
#include "m_dpsaveenv.h"
#include "dpcom/dpsaveline.h"
#include "m_sql/m_dblinerecords.h"

class M_DpSaveLineRecord : public DpSaveLine
{
    Q_OBJECT
public:
    explicit M_DpSaveLineRecord(QObject *parent = nullptr);

protected:
    void insertItem(DbLineRecordItem &item){M_DbLineRecords::bulid()->insertItem(item);}
};

#endif // M_DPSLAVELINERECORD_H
