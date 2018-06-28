#ifndef MPDURTUTEST_SWITEMWID_H
#define MPDURTUTEST_SWITEMWID_H

#include "../rtu/mpdurtutestthread.h"

namespace Ui {
class MpduRtuTest_SwItemWid;
}

class MpduRtuTest_SwItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_SwItemWid(QWidget *parent = 0);
    ~MpduRtuTest_SwItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setOpen(bool checked);
    void setClose(bool checked);

    bool select();
    int status();
private:
    Ui::MpduRtuTest_SwItemWid *ui;
};

#endif // MPDURTUTEST_SWITEMWID_H
