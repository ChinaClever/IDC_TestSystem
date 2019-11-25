#ifndef MV1_DBOUTPUTRECORDS_H
#define MV1_DBOUTPUTRECORDS_H
#include "sqlcom/dboutputrecords.h"

#define MV1_DB_OutputRecords "mv1_output_records"

class MV1_DbOutputRecords : public DbOutputRecords
{
    MV1_DbOutputRecords();
public:
    static MV1_DbOutputRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(MV1_DB_OutputRecords) ;}
};

#endif // MV1_DBOUTPUTRECORDS_H
