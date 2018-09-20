#ifndef ZTEST_OUTPUTELEWID_H
#define ZTEST_OUTPUTELEWID_H

#include <QWidget>
#include "ztest_eleitemwid.h"
#include "z_setting/z_testrtu/ztest_rtuthread.h"

namespace Ui {
class ZTest_OutputEleWid;
}

class ZTest_OutputEleWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_OutputEleWid(QWidget *parent = 0);
    ~ZTest_OutputEleWid();

protected:
    void initwid();

protected slots:
    void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_cleanRadio_clicked(bool checked);

private:
    Ui::ZTest_OutputEleWid *ui;
    ZTest_RtuThread *mRtu;
    ZTest_EleItemWid *mWid[24];
    int mReg;
};

#endif // ZTEST_OUTPUTELEWID_H
