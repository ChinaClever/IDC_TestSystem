#ifndef MV1_DPSAVELINETHRESHOLD_H
#define MV1_DPSAVELINETHRESHOLD_H
#include "mv1_dpalarmsave.h"
#include "mv1_sql/mv1_dblinethresholds.h"
#include "dpcom/dpsavelinethreshold.h"

class MV1_DpSaveLineThreshold : public DpSaveLineThreshold
{
    Q_OBJECT
public:
    explicit MV1_DpSaveLineThreshold(QObject *parent = nullptr);

protected:
    void insertItem(DbLineThresholdItem &item){MV1_DbLineThresholds::bulid()->insertItem(item);}
};

#endif // MV1_DPSAVELINETHRESHOLD_H
