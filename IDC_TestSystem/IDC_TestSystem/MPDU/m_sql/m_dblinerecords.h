#ifndef M_DBLINERECORDS_H
#define M_DBLINERECORDS_H
#include "sqlcom/dblinerecords.h"

#define M_DB_RealRecords "m_line_records"

class M_DbLineRecords : public DbLineRecords
{
    M_DbLineRecords();
public:
    static M_DbLineRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(M_DB_RealRecords) ;}
};

#endif // M_DBLINERECORDS_H
