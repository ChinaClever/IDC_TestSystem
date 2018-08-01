#ifndef IP_TRANSTABLEWID_H
#define IP_TRANSTABLEWID_H

#include "ip_thresholdtablewid.h"

class IP_TransTableWid : public TransTableWid
{
    Q_OBJECT
public:
    explicit IP_TransTableWid(QWidget *parent = nullptr);

};

#endif // IP_TRANSTABLEWID_H
