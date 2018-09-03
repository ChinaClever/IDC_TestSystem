#ifndef ZTEST_THRESHOLDOUTPUTWID_H
#define ZTEST_THRESHOLDOUTPUTWID_H

#include <QWidget>
#include "ztest_thresholditemwid.h"
namespace Ui {
class ZTest_ThresholdOutputWid;
}

class ZTest_ThresholdOutputWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_ThresholdOutputWid(QWidget *parent = 0);
    ~ZTest_ThresholdOutputWid();
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
    Ui::ZTest_ThresholdOutputWid *ui;
    ZTest_RtuThread *mRtu;
    int mReg;

    ZTest_ThresholdItemWid *mWid[24];
};

#endif // ZTEST_THRESHOLDOUTPUTWID_H
