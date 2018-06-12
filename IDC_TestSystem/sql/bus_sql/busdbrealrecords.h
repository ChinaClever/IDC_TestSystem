#ifndef BUSDBREALRECORDS_H
#define BUSDBREALRECORDS_H
#include "busdbthresholds.h"

#define BUS_DB_RealRecords "bus_real_records"

struct BusDbRealRecordItem : public DbBasicItem {
     QString bus, box, loop, sw_str;
    double vol, cur, pow, apow, pf, ele;
};


class BusDbRealRecords : public SqlBasic<BusDbRealRecordItem>
{
    BusDbRealRecords();
public:
    static BusDbRealRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(BUS_DB_RealRecords) ;}
    bool insertItem(BusDbRealRecordItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const BusDbRealRecordItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,BusDbRealRecordItem &item);
};

#endif // BUSDBREALRECORDS_H
