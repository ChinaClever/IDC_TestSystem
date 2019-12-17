#ifndef MV1_DBENV_H
#define MV1_DBENV_H
#include "sqlcom/dbenv.h"

#define MV1_DB_Env "mv1_env_sensor"

class MV1_DbEnv : public DbEnv
{
    MV1_DbEnv();
public:
    static MV1_DbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(MV1_DB_Env) ;}
};

#endif // MV1_DBENV_H
