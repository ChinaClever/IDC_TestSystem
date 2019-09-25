#ifndef ZSET_SWITEMWID_H
#define ZSET_SWITEMWID_H

#include "../z_setrtu/zset_rtuthread.h"
#include "../z_setsnmp/zset_snmpthread.h"
#include "common.h"

namespace Ui {
class ZSet_SwItemWid;
}

class ZSet_SwItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_SwItemWid(QWidget *parent = 0);
    ~ZSet_SwItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setOpen(bool checked);
    void setClose(bool checked);

    bool select();
    int status();

private:
    Ui::ZSet_SwItemWid *ui;
};

#endif // ZSET_SWITEMWID_H
