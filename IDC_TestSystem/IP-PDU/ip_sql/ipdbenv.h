#ifndef IPDBENV_H
#define IPDBENV_H
#include "sqlcom/dbenv.h"

#define IP_DB_Env "ip_env_sensor"

class IpDbEnv : public DbEnv
{
    IpDbEnv();
public:
    static IpDbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_Env) ;}
};

#endif // IPDBENV_H
