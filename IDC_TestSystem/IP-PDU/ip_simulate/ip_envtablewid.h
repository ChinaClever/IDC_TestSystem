#ifndef IP_ENVTABLEWID_H
#define IP_ENVTABLEWID_H

#include "ip_devtablewid.h"

class IP_EnvTableWid : public IP_DevTableWid
{
    Q_OBJECT
public:
    explicit IP_EnvTableWid(QWidget *parent = nullptr);

public slots:
    void updateData();

protected:
    void initWid();
    void setAlarm(IP_RtuRecvLine &unit, int line, int row);
    void setObjUnit(IP_RtuRecvLine &unit, int line, QStringList &list);
};

#endif // IP_ENVTABLEWID_H
