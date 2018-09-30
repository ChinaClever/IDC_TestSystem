#ifndef MSET_SWCYCLEITEMWID_H
#define MSET_SWCYCLEITEMWID_H

#include <QWidget>
#include "../m_setrtu/mset_rtuthread.h"
#include "../m_setsnmp/mset_snmpthread.h"
#include "common.h"
namespace Ui {
class MSet_SwCycleItemWid;
}

class MSet_SwCycleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_SwCycleItemWid(QWidget *parent = 0);
    ~MSet_SwCycleItemWid();

    void init(int id);
    void setSelect(bool checked);
    bool select();
    int status();

private:
    Ui::MSet_SwCycleItemWid *ui;
};
#endif // MSET_SWCYCLEITEMWID_H
