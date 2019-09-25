#ifndef R_DBENV_H
#define R_DBENV_H
#include "sqlcom/dbenv.h"

#define R_DB_Env "r_env_sensor"

class R_DbEnv : public DbEnv
{
    R_DbEnv();
public:
    static R_DbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(R_DB_Env) ;}
};


#endif // R_DBENV_H
