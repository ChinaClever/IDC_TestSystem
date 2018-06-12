#ifndef SIDBTHRESHOLDS_H
#define SIDBTHRESHOLDS_H
#include "sidbrealrecords.h"

#define SI_DB_Thresholds "si_dev_thresholds"

struct SiDbThresholdItem : public DbBasicItem {
    int dev_id, line;
    double vol, vol_min, vol_max, cur, cur_min, cur_max;
};


class SiDbThresholds : public SqlBasic<SiDbThresholdItem>
{
    SiDbThresholds();
public:
    static SiDbThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_Thresholds) ;}
    bool insertItem(SiDbThresholdItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const SiDbThresholdItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,SiDbThresholdItem &item);
};

#endif // SIDBTHRESHOLDS_H
