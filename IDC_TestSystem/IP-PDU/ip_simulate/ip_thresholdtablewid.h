#ifndef IP_THRESHOLDTABLEWID_H
#define IP_THRESHOLDTABLEWID_H

#include "ip_envtablewid.h"

class IP_ThresholdTableWid : public LineThresholdTableWid
{
    Q_OBJECT
public:
    explicit IP_ThresholdTableWid(QWidget *parent = nullptr);

};

#endif // IP_THRESHOLDTABLEWID_H
