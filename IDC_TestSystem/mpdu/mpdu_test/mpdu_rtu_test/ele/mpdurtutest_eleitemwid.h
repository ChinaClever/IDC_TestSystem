#ifndef MPDURTUTEST_ELEITEMWID_H
#define MPDURTUTEST_ELEITEMWID_H

#include "../rtu/mpdurtutestthread.h"

namespace Ui {
class MpduRtuTest_EleItemWid;
}

class MpduRtuTest_EleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_EleItemWid(QWidget *parent = 0);
    ~MpduRtuTest_EleItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setClean(bool checked);

    bool select();
    int status();
private slots:
    void on_cleanRadio_clicked();

private:
    Ui::MpduRtuTest_EleItemWid *ui;
};

#endif // MPDURTUTEST_ELEITEMWID_H
