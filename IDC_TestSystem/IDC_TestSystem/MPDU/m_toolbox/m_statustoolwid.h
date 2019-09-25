#ifndef M_STATUSTOOLWID_H
#define M_STATUSTOOLWID_H

#include "m_settingtoolwid.h"

namespace Ui {
class M_StatusToolWid;
}

class M_StatusToolWid : public StatusToolWid
{
    Q_OBJECT
public:
    explicit M_StatusToolWid(QWidget *parent = 0);

};

#endif // M_STATUSTOOLWID_H
