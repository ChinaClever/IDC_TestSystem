#ifndef BUSDBALARM_H
#define BUSDBALARM_H
#include "busdbenv.h"

#define BUS_DB_Alarms "bus_dev_alarms"

struct BusDbAlarmItem : public DbBasicItem {
    QString bus, box, loop;
    QString type_str,msg;
};


class BusDbAlarm : public SqlBasic<BusDbAlarmItem>
{
    BusDbAlarm();
public:
    static BusDbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(BUS_DB_Alarms);}
    bool insertItem(BusDbAlarmItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const BusDbAlarmItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,BusDbAlarmItem &item);
};

#endif // BUSDBALARM_H
