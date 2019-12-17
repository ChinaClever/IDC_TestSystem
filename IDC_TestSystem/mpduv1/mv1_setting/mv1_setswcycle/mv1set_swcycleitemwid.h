#ifndef MV1SET_SWCYCLEITEMWID_H
#define MV1SET_SWCYCLEITEMWID_H

#include <QWidget>
#include "../mv1_setrtu/mv1set_rtuthread.h"
#include "../mv1_setsnmp/mv1set_snmpthread.h"
#include "common.h"
namespace Ui {
class MV1Set_SwCycleItemWid;
}

class MV1Set_SwCycleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_SwCycleItemWid(QWidget *parent = 0);
    ~MV1Set_SwCycleItemWid();

    void init(int id);
    void setSelect(bool checked);
    bool select();
    int status();

private:
    Ui::MV1Set_SwCycleItemWid *ui;
};
#endif // MV1SET_SWCYCLEITEMWID_H
