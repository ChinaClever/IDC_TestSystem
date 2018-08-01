#ifndef IP_DEVTABLEWID_H
#define IP_DEVTABLEWID_H

#include "tablewid/transtablewid.h"
#include "ip_com/ipdatapackets.h"

class IP_DevTableWid : public LineTableWid
{
    Q_OBJECT
public:
    explicit IP_DevTableWid(QWidget *parent = nullptr);

};

#endif // IP_DEVTABLEWID_H
