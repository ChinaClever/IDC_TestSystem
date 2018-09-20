#ifndef ZTEST_LOOPWID_H
#define ZTEST_LOOPWID_H

#include <QWidget>
#include "ztest_loopunitwid.h"
namespace Ui {
class ZTest_LoopWid;
}

class ZTest_LoopWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_LoopWid(QWidget *parent = 0);
    ~ZTest_LoopWid();
protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();


private:
    Ui::ZTest_LoopWid *ui;
    ZSet_RtuThread *mRtu;
    ZTest_LoopUnitWid *mWid;
};

#endif // ZTEST_LOOPWID_H
