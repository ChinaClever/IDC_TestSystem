#ifndef M_DBOUTPUTRECORDS_H
#define M_DBOUTPUTRECORDS_H
#include "sqlcom/dboutputrecords.h"

#define M_DB_OutputRecords "m_output_records"

class M_DbOutputRecords : public DbOutputRecords
{
    M_DbOutputRecords();
public:
    static M_DbOutputRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(M_DB_OutputRecords) ;}
};

#endif // M_DBOUTPUTRECORDS_H
