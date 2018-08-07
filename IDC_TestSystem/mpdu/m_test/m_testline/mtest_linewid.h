#ifndef MTEST_LINEWID_H
#define MTEST_LINEWID_H

#include "mtest_lineunitwid.h"

namespace Ui {
class MTest_LineWid;
}

class MTest_LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_LineWid(QWidget *parent = 0);
    ~MTest_LineWid();

protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MTest_LineWid *ui;
    MTest_RtuThread *mRtu;
    MTest_LineUnitWid *mWid[3];
};

#endif // MTEST_LINEWID_H
