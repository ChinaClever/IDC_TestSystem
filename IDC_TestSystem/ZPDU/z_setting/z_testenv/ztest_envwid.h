#ifndef ZTEST_ENVWID_H
#define ZTEST_ENVWID_H

#include <QWidget>
#include "ztest_envunitwid.h"
namespace Ui {
class ZTest_EnvWid;
}

class ZTest_EnvWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_EnvWid(QWidget *parent = 0);
    ~ZTest_EnvWid();
protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ZTest_EnvWid *ui;
    ZSet_RtuThread *mRtu;
    ZTest_EnvUnitWid *mWid[2];
};

#endif // ZTEST_ENVWID_H
