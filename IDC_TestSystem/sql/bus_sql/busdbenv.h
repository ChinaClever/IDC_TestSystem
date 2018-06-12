#ifndef BUSDBENV_H
#define BUSDBENV_H
#include "busdbmodbuscmd.h"

#define BUS_DB_Env "bus_env_sensor"

struct BusDbEnvItem : public DbBasicItem {
    QString bus, box, loop;
    int tem, tem_min, tem_max;
};


class BusDbEnv : public SqlBasic<BusDbEnvItem>
{
    BusDbEnv();
public:
    static BusDbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(BUS_DB_Env);}
    bool insertItem(BusDbEnvItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const BusDbEnvItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,BusDbEnvItem &item);
};

#endif // BUSDBENV_H
