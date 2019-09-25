#ifndef ELOAD_DBENV_H
#define ELOAD_DBENV_H
#include "sqlcom/dbenv.h"

#define ELoad_DB_Env "eload_env_sensor"

class ELoad_DbEnv : public DbEnv
{
    ELoad_DbEnv();
public:
    static ELoad_DbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(ELoad_DB_Env) ;}
};


#endif // ELOAD_DBENV_H
