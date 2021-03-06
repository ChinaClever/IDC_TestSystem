#ifndef IP_DPSLAVEENV_H
#define IP_DPSLAVEENV_H

#include "ip_dpsavethreshold.h"
#include "ip_sql/ipdbenv.h"
#include "dpcom/dpsaveenv.h"

class IP_DpSaveEnv : public DpSaveEnv
{
    Q_OBJECT
public:
    explicit IP_DpSaveEnv(QObject *parent = nullptr);

protected:
    void insertItem(DbEnvItem &item){IpDbEnv::bulid()->insertItem(item);}
};

#endif // IP_DPSLAVEENV_H
