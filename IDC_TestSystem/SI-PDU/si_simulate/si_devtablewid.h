#ifndef SI_DEVTABLEWID_H
#define SI_DEVTABLEWID_H

#include "si_transtablewid.h"
#include "tablewid/linetablewid.h"

class SI_DevTableWid : public LineTableWid
{
    Q_OBJECT
public:
    explicit SI_DevTableWid(QWidget *parent = nullptr);
};

#endif // SI_DEVTABLEWID_H
