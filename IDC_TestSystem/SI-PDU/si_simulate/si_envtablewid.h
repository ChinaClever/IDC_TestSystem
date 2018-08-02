#ifndef SI_ENVTABLEWID_H
#define SI_ENVTABLEWID_H

#include "tablewid/envtablewid.h"
#include "si_com/sidatapackets.h"

class SI_EnvTableWid : public EnvTableWid
{
    Q_OBJECT
public:
    explicit SI_EnvTableWid(QWidget *parent = nullptr);
};

#endif // SI_ENVTABLEWID_H
