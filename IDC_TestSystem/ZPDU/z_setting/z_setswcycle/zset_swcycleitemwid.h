#ifndef ZSET_SWCYCLEITEMWID_H
#define ZSET_SWCYCLEITEMWID_H

#include <QWidget>
#include "../z_setrtu/zset_rtuthread.h"
#include "../z_setsnmp/zset_snmpthread.h"
#include "common.h"
namespace Ui {
class ZSet_SwCycleItemWid;
}

class ZSet_SwCycleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_SwCycleItemWid(QWidget *parent = 0);
    ~ZSet_SwCycleItemWid();

    void init(int id);
    void setSelect(bool checked);
    bool select();
    int status();

private:
    Ui::ZSet_SwCycleItemWid *ui;
};

#endif // ZSET_SWCYCLEITEMWID_H
