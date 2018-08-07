#ifndef MTEST_ENVWID_H
#define MTEST_ENVWID_H

#include "mtest_envunitwid.h"

namespace Ui {
class MTest_EnvWid;
}

class MTest_EnvWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_EnvWid(QWidget *parent = 0);
    ~MTest_EnvWid();

protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MTest_EnvWid *ui;
    MTest_RtuThread *mRtu;
    MTest_EnvUnitWid *mWid[2];
};

#endif // MTEST_ENVWID_H
