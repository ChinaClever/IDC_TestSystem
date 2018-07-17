#ifndef IP_DEVTABLEWID_H
#define IP_DEVTABLEWID_H

#include "comtablewid.h"
#include "ip_com/ipdatapackets.h"

class IP_DevTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit IP_DevTableWid(QWidget *parent = nullptr);


public slots:
    void updateData();

protected:
    virtual void initWid();
    virtual void setAlarm(IP_RtuRecvLine &unit, int line, int row);
    virtual void setObjUnit(IP_RtuRecvLine &unit, int line, QStringList &list);
    virtual int updateDev(IP_Rtu_Recv &dev, int line, int row);
};

#endif // IP_DEVTABLEWID_H
