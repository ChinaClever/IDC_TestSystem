#ifndef ZTEST_SWITEMWID_H
#define ZTEST_SWITEMWID_H

#include "../z_testrtu/ztest_rtuthread.h"

namespace Ui {
class ZTest_SwItemWid;
}

class ZTest_SwItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_SwItemWid(QWidget *parent = 0);
    ~ZTest_SwItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setOpen(bool checked);
    void setClose(bool checked);

    bool select();
    int status();

private:
    Ui::ZTest_SwItemWid *ui;
};

#endif // ZTEST_SWITEMWID_H
