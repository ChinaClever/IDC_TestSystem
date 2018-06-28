#ifndef MPDURTUTEST_LINEWID_H
#define MPDURTUTEST_LINEWID_H

#include "mpdurtutest_lineunitwid.h"

namespace Ui {
class MpduRtuTest_LineWid;
}

class MpduRtuTest_LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_LineWid(QWidget *parent = 0);
    ~MpduRtuTest_LineWid();

    void initWid(SerialPort *serial);

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MpduRtuTest_LineWid *ui;
    MpduRtuTestThread *mRtu;
    MpduRtuTest_LineUnitWid *mWid[3];
};

#endif // MPDURTUTEST_LINEWID_H
