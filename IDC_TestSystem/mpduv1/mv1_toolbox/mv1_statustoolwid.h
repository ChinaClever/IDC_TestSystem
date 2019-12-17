#ifndef MV1_STATUSTOOLWID_H
#define MV1_STATUSTOOLWID_H

#include "mv1_settingtoolwid.h"

namespace Ui {
class MV1_StatusToolWid;
}

class MV1_StatusToolWid : public StatusToolWid
{
    Q_OBJECT
public:
    explicit MV1_StatusToolWid(QWidget *parent = 0);

};

#endif // MV1_STATUSTOOLWID_H
