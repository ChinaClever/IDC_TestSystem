#ifndef Z_DBENV_H
#define Z_DBENV_H
#include "sqlcom/dbenv.h"

#define Z_DB_Env "z_env_sensor"

class Z_DbEnv : public DbEnv
{
    Z_DbEnv();
public:
    static Z_DbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(Z_DB_Env) ;}
};


#endif // Z_DBENV_H
