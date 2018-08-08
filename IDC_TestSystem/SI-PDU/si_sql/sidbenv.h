#ifndef SIDBENV_H
#define SIDBENV_H
#include "sqlcom/dbenv.h"

#define SI_DB_Env "si_env_sensor"

class SiDbEnv : public DbEnv
{
    SiDbEnv();
public:
    static SiDbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_Env) ;}
};

#endif // SIDBENV_H
