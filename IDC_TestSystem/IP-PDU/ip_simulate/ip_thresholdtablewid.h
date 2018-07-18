#ifndef IP_THRESHOLDTABLEWID_H
#define IP_THRESHOLDTABLEWID_H

#include "ip_envtablewid.h"

class IP_ThresholdTableWid : public IP_DevTableWid
{
    Q_OBJECT
public:
    explicit IP_ThresholdTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(IP_RtuRecvLine &unit, int line, int row);
    void setObjUnit(IP_RtuRecvLine &unit, int line, QStringList &list);
};

#endif // IP_THRESHOLDTABLEWID_H
