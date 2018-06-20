#ifndef MPDURTUTEST_SWWID_H
#define MPDURTUTEST_SWWID_H

#include "mpdurtutest_switemwid.h"
#include "../rtu/mpdurtutestthread.h"

namespace Ui {
class MpduRtuTest_SwWid;
}

class MpduRtuTest_SwWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_SwWid(QWidget *parent = 0);
    ~MpduRtuTest_SwWid();

    void initwid(SerialPort *serial);

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_openRadio_clicked(bool checked);

    void on_closeRadio_clicked(bool checked);


private:
    Ui::MpduRtuTest_SwWid *ui;
    MpduRtuTestThread *mRtu;
    MpduRtuTest_SwItemWid *mWid[24];
    int mReg;
};

#endif // MPDURTUTEST_SWWID_H
