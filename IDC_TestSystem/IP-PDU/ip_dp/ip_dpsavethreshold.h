#ifndef IP_DPSAVETHRESHOLD_H
#define IP_DPSAVETHRESHOLD_H

#include "ip_dpslaverecord.h"

class IP_DpSaveThreshold : public IP_DpSlaveRecord
{
    Q_OBJECT
public:
    explicit IP_DpSaveThreshold(QObject *parent = nullptr);

protected:
    void saveLogItem(int id);
};

#endif // IP_DPSAVETHRESHOLD_H
