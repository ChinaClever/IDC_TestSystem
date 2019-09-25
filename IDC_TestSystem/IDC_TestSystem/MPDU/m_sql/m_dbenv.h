#ifndef M_DBENV_H
#define M_DBENV_H
#include "sqlcom/dbenv.h"

#define M_DB_Env "m_env_sensor"

class M_DbEnv : public DbEnv
{
    M_DbEnv();
public:
    static M_DbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(M_DB_Env) ;}
};

#endif // M_DBENV_H
