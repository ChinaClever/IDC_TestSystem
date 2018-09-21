#ifndef MSET_SWITEMWID_H
#define MSET_SWITEMWID_H

#include "../m_setrtu/mset_rtuthread.h"
#include "../m_setsnmp/mset_snmpthread.h"

namespace Ui {
class MSet_SwItemWid;
}

class MSet_SwItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_SwItemWid(QWidget *parent = 0);
    ~MSet_SwItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setOpen(bool checked);
    void setClose(bool checked);

    bool select();
    int status();

private:
    Ui::MSet_SwItemWid *ui;
};

extern void com_setBackColour(const QString &,QWidget *target);

#endif // MSET_SWITEMWID_H
