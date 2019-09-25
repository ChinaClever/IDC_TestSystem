#ifndef BUSDBTHRESHOLDS_H
#define BUSDBTHRESHOLDS_H
#include "sqlcom/basicsql.h"

#define BUS_DB_Thresholds "bus_loop_thresholds"

struct BusDbThresholdItem : public DbBasicItem {
    QString bus, box, loop;
    double vol, vol_min, vol_max, cur, cur_min, cur_max;
};


class BusDbThresholds : public SqlBasic<BusDbThresholdItem>
{
    BusDbThresholds();
public:
    static BusDbThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(BUS_DB_Thresholds) ;}
    bool insertItem(BusDbThresholdItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const BusDbThresholdItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,BusDbThresholdItem &item);
};

#endif // BUSDBTHRESHOLDS_H
