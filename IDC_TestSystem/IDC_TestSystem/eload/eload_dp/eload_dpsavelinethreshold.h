#ifndef ELOAD_DPSAVELINETHRESHOLD_H
#define ELOAD_DPSAVELINETHRESHOLD_H
#include "ELoad_dpsavelinerecord.h"
#include "ELoad_sql/ELoad_dblinethresholds.h"
#include "dpcom/dpsavelinethreshold.h"

class ELoad_DpSaveLineThreshold : public DpSaveLineThreshold
{
    Q_OBJECT
public:
    explicit ELoad_DpSaveLineThreshold(QObject *parent = nullptr);

protected:
    void saveLogItem(int id);
    void insertItem(DbLineThresholdItem &item){ELoad_DbLineThresholds::bulid()->insertItem(item);}
};

#endif // ELOAD_DPSAVELINETHRESHOLD_H
