#ifndef R_DBLINETHRESHOLDS_H
#define R_DBLINETHRESHOLDS_H
#include "sqlcom/dblinethresholds.h"

#define R_DB_Thresholds "r_line_thresholds"

class R_DbLineThresholds : public DbLineThresholds
{
    R_DbLineThresholds();
public:
    static R_DbLineThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(R_DB_Thresholds) ;}
};

#endif // R_DBLINETHRESHOLDS_H
