#ifndef Z_DBOUTPUTRECORDS_H
#define Z_DBOUTPUTRECORDS_H
#include "sqlcom/dboutputrecords.h"

#define Z_DB_OutputRecords "z_output_records"

class Z_DbOutputRecords : public DbOutputRecords
{
    Z_DbOutputRecords();
public:
    static Z_DbOutputRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(Z_DB_OutputRecords) ;}
};

#endif // Z_DBOUTPUTRECORDS_H
