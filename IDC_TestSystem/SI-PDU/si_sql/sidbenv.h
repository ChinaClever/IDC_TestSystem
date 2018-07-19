#ifndef SIDBENV_H
#define SIDBENV_H
#include "sidbmodbustrans.h"

#define SI_DB_Env "si_env_sensor"

struct SiDbEnvItem : public DbBasicItem {
    int dev_id;
    int tem, tem_min, tem_max, hum, hum_min, hum_max;
};

class SiDbEnv : public SqlBasic<SiDbEnvItem>
{
public:
    SiDbEnv();
    static SiDbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_Env) ;}
    bool insertItem(SiDbEnvItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const SiDbEnvItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,SiDbEnvItem &item);
};

#endif // SIDBENV_H
