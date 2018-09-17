#ifndef MTEST_SWITEMWID_H
#define MTEST_SWITEMWID_H

#include "../m_testrtu/mtest_rtuthread.h"
#include "../m_testsnmp/mtest_snmpthread.h"

namespace Ui {
class MTest_SwItemWid;
}

class MTest_SwItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_SwItemWid(QWidget *parent = 0);
    ~MTest_SwItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setOpen(bool checked);
    void setClose(bool checked);

    bool select();
    int status();

private:
    Ui::MTest_SwItemWid *ui;
};

extern void com_setBackColour(const QString &,QWidget *target);

#endif // MTEST_SWITEMWID_H
