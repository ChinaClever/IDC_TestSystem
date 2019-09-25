#ifndef RSET_SWCYCLEITEMWID_H
#define RSET_SWCYCLEITEMWID_H

#include <QWidget>
#include "../r_setrtu/rset_rtuthread.h"
#include "../r_setsnmp/rset_snmpthread.h"
#include "common.h"
namespace Ui {
class RSet_SwCycleItemWid;
}

class RSet_SwCycleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_SwCycleItemWid(QWidget *parent = 0);
    ~RSet_SwCycleItemWid();
    void init(int id);
    void setSelect(bool checked);
    bool select();
    int status();

private:
    Ui::RSet_SwCycleItemWid *ui;
};

#endif // RSET_SWCYCLEITEMWID_H
