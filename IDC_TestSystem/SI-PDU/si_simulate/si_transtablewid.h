#ifndef SI_TRANSTABLEWID_H
#define SI_TRANSTABLEWID_H

#include "si_thresholdtablewid.h"
#include "tablewid/transtablewid.h"

class SI_TransTableWid : public TransTableWid
{
    Q_OBJECT
public:
    explicit SI_TransTableWid(QWidget *parent = nullptr);
};

#endif // SI_TRANSTABLEWID_H
