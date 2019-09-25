#ifndef RSET_SWITEMWID_H
#define RSET_SWITEMWID_H

#include "../r_setrtu/rset_rtuthread.h"
#include "../r_setsnmp/rset_snmpthread.h"
#include "common.h"

namespace Ui {
class RSet_SwItemWid;
}

class RSet_SwItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_SwItemWid(QWidget *parent = 0);
    ~RSet_SwItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setOpen(bool checked);
    void setClose(bool checked);

    bool select();
    int status();

private:
    Ui::RSet_SwItemWid *ui;
};

#endif // RSET_SWITEMWID_H
