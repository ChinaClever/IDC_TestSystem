#ifndef MPDURTUTEST_OUTPUTELEWID_H
#define MPDURTUTEST_OUTPUTELEWID_H

#include "mpdurtutest_eleitemwid.h"

namespace Ui {
class MpduRtuTest_OutputEleWid;
}

class MpduRtuTest_OutputEleWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_OutputEleWid(QWidget *parent = 0);
    ~MpduRtuTest_OutputEleWid();

    void initwid(SerialPort *serial);

protected slots:
    void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_cleanRadio_clicked(bool checked);

private:
    Ui::MpduRtuTest_OutputEleWid *ui;
    MpduRtuTestThread *mRtu;
    MpduRtuTest_EleItemWid *mWid[24];
    int mReg;
};

#endif // MPDURTUTEST_OUTPUTELEWID_H
