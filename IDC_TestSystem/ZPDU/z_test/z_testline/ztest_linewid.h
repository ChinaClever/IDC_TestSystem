#ifndef ZTEST_LINEWID_H
#define ZTEST_LINEWID_H

#include <QWidget>
#include "ztest_lineunitwid.h"
namespace Ui {
class ZTest_LineWid;
}

class ZTest_LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_LineWid(QWidget *parent = 0);
    ~ZTest_LineWid();

protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ZTest_LineWid *ui;
    ZTest_RtuThread *mRtu;
    ZTest_LineUnitWid *mWid[2];
};

#endif // ZTEST_LINEWID_H
