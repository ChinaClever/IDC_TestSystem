#ifndef SIDBALARM_H
#define SIDBALARM_H
#include "sidbthresholds.h"

#define SI_DB_Alarms "si_dev_alarms"

struct SiDbAlarmItem : public DbBasicItem {
    int dev_id, line;
    QString type_str,msg;
};


class SiDbAlarm : public SqlBasic<SiDbAlarmItem>
{
    SiDbAlarm();
public:
    static SiDbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_Alarms);}
    bool insertItem(SiDbAlarmItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const SiDbAlarmItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,SiDbAlarmItem &item);
};

#endif // SIDBALARM_H
