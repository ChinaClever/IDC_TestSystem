#ifndef MPDURTUTEST_ENVWID_H
#define MPDURTUTEST_ENVWID_H

#include "mpdurtutest_envunitwid.h"

namespace Ui {
class MpduRtuTest_EnvWid;
}

class MpduRtuTest_EnvWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_EnvWid(QWidget *parent = 0);
    ~MpduRtuTest_EnvWid();

    void initWid(SerialPort *serial);

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MpduRtuTest_EnvWid *ui;
    MpduRtuTestThread *mRtu;
    MpduRtuTest_EnvUnitWid *mWid[2];
};

#endif // MPDURTUTEST_ENVWID_H
