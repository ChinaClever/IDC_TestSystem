#ifndef MPDURTUTEST_THRESHOLDOUTPUTWID_H
#define MPDURTUTEST_THRESHOLDOUTPUTWID_H

#include "mpdurtutest_thresholditemwid.h"
#include "../rtu/mpdurtutestthread.h"

namespace Ui {
class MpduRtuTest_ThresholdOutputWid;
}

class MpduRtuTest_ThresholdOutputWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_ThresholdOutputWid(QWidget *parent = 0);
    ~MpduRtuTest_ThresholdOutputWid();

    void initwid(int mode, SerialPort *serial);

protected:
    int getReg(int mode);

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_curSpinBox_valueChanged(int arg1);

private:
    Ui::MpduRtuTest_ThresholdOutputWid *ui;
    MpduRtuTestThread *mRtu;
    int mReg;

    MpduRtuTest_ThresholdItemWid *mWid[24];
};

#endif // MPDURTUTEST_THRESHOLDOUTPUTWID_H
