#ifndef MV1SET_SWITEMWID_H
#define MV1SET_SWITEMWID_H

#include "../mv1_setrtu/mv1set_rtuthread.h"
#include "../mv1_setsnmp/mv1set_snmpthread.h"

namespace Ui {
class MV1Set_SwItemWid;
}

class MV1Set_SwItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_SwItemWid(QWidget *parent = 0);
    ~MV1Set_SwItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setOpen(bool checked);
    void setClose(bool checked);

    bool select();
    int status();

private:
    Ui::MV1Set_SwItemWid *ui;
};

extern void com_setBackColour(const QString &,QWidget *target);

#endif // MV1SET_SWITEMWID_H
