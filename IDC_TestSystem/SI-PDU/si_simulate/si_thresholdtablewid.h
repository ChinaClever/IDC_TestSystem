#ifndef SI_THRESHOLDTABLEWID_H
#define SI_THRESHOLDTABLEWID_H

#include "si_envtablewid.h"
#include "tablewid/linethresholdtablewid.h"

class SI_ThresholdTableWid : public LineThresholdTableWid
{
    Q_OBJECT
public:
    explicit SI_ThresholdTableWid(QWidget *parent = nullptr);

};

#endif // SI_THRESHOLDTABLEWID_H
