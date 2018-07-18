#ifndef IP_TRANSTABLEWID_H
#define IP_TRANSTABLEWID_H

#include "ip_thresholdtablewid.h"

class IP_TransTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit IP_TransTableWid(QWidget *parent = nullptr);

public slots:
    void updateData();

protected:
    void initWid();
    void setAlarm(int err, int row);
    void setObjUnit(IP_RtuCount &unit, QStringList &list);
    int updateDev(IpDevPacket *dev, int row);
};

#endif // IP_TRANSTABLEWID_H
