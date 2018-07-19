#ifndef IP_DPSLAVETRANS_H
#define IP_DPSLAVETRANS_H

#include "ip_dpslaveenv.h"

class IP_DpSlaveTrans : public IP_DpSlaveRecord
{
    Q_OBJECT
public:
    explicit IP_DpSlaveTrans(QObject *parent = nullptr);

protected:
    void saveLogItem(int id);
};

#endif // IP_DPSLAVETRANS_H
