#ifndef IPDBENV_H
#define IPDBENV_H
#include "si_sql/sidbenv.h"

#define IP_DB_Env "ip_env_sensor"
typedef SiDbEnvItem IpDbEnvItem;

class IpDbEnv : public SiDbEnv
{
    IpDbEnv();
public:
    static IpDbEnv *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_Env) ;}
};

#endif // IPDBENV_H
