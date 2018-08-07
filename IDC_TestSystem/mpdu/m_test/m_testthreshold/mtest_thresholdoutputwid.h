#ifndef MTEST_THRESHOLDOUTPUTWID_H
#define MTEST_THRESHOLDOUTPUTWID_H

#include "mtest_thresholditemwid.h"

namespace Ui {
class MTest_ThresholdOutputWid;
}

class MTest_ThresholdOutputWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_ThresholdOutputWid(QWidget *parent = 0);
    ~MTest_ThresholdOutputWid();

    void initwid(int mode);

protected:
    int getReg(int mode);

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_curSpinBox_valueChanged(int arg1);

private:
    Ui::MTest_ThresholdOutputWid *ui;
    MTest_RtuThread *mRtu;
    int mReg;

    MTest_ThresholdItemWid *mWid[24];
};

#endif // MTEST_THRESHOLDOUTPUTWID_H
