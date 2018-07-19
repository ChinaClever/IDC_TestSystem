#ifndef IP_DPSLAVEENV_H
#define IP_DPSLAVEENV_H

#include "ip_dpsavethreshold.h"

class IP_DpSlaveEnv : public IP_DpSlaveRecord
{
    Q_OBJECT
public:
    explicit IP_DpSlaveEnv(QObject *parent = nullptr);

protected:
    void saveLogItem(int id);
};

#endif // IP_DPSLAVEENV_H
