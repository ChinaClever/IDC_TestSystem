#ifndef MTEST_OUTPUTELEWID_H
#define MTEST_OUTPUTELEWID_H

#include "mtest_eleitemwid.h"

namespace Ui {
class MTest_OutputEleWid;
}

class MTest_OutputEleWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_OutputEleWid(QWidget *parent = 0);
    ~MTest_OutputEleWid();

protected:
    void initwid();

protected slots:
    void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_cleanRadio_clicked(bool checked);

private:
    Ui::MTest_OutputEleWid *ui;
    MTest_RtuThread *mRtu;
    MTest_EleItemWid *mWid[24];
    int mReg;
};

#endif // MTEST_OUTPUTELEWID_H
