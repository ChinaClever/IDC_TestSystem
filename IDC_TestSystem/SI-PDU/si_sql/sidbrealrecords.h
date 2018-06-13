#ifndef SIDBREALRECORDS_H
#define SIDBREALRECORDS_H
#include "sidbenv.h"

#define SI_DB_RealRecords "si_real_records"

struct SiDbRealRecordItem : public DbBasicItem {
    int dev_id, line, sw;
    QString sw_str;
    double vol, cur, pow, apow, pf, ele;
};

class SiDbRealRecords : public SqlBasic<SiDbRealRecordItem>
{
    SiDbRealRecords();
public:
    static SiDbRealRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_RealRecords) ;}
    bool insertItem(SiDbRealRecordItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const SiDbRealRecordItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,SiDbRealRecordItem &item);
};

#endif // SIDBREALRECORDS_H
