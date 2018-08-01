#ifndef IP_ENVTABLEWID_H
#define IP_ENVTABLEWID_H

#include "ip_devtablewid.h"

class IP_EnvTableWid : public EnvTableWid
{
    Q_OBJECT
public:
    explicit IP_EnvTableWid(QWidget *parent = nullptr);

};

#endif // IP_ENVTABLEWID_H
