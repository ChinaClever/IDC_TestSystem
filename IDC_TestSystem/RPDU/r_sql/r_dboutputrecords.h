#ifndef R_DBOUTPUTRECORDS_H
#define R_DBOUTPUTRECORDS_H
#include "sqlcom/dboutputrecords.h"

#define R_DB_OutputRecords "r_output_records"

class R_DbOutputRecords : public DbOutputRecords
{
    R_DbOutputRecords();
public:
    static R_DbOutputRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(R_DB_OutputRecords) ;}
};

#endif // R_DBOUTPUTRECORDS_H
