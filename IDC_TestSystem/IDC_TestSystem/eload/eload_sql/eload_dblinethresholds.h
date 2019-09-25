#ifndef ELOAD_DBLINETHRESHOLDS_H
#define ELOAD_DBLINETHRESHOLDS_H
#include "sqlcom/dblinethresholds.h"

#define ELoad_DB_Thresholds "eload_line_thresholds"

class ELoad_DbLineThresholds : public DbLineThresholds
{
    ELoad_DbLineThresholds();
public:
    static ELoad_DbLineThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(ELoad_DB_Thresholds) ;}
};

#endif // ELOAD_DBLINETHRESHOLDS_H
