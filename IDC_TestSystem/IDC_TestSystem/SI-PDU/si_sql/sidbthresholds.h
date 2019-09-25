#ifndef SIDBTHRESHOLDS_H
#define SIDBTHRESHOLDS_H
#include "sqlcom/dblinethresholds.h"

#define SI_DB_Thresholds "si_line_thresholds"

class SiDbThresholds : public DbLineThresholds
{
    SiDbThresholds();
public:
    static SiDbThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_Thresholds) ;}   
};

#endif // SIDBTHRESHOLDS_H
