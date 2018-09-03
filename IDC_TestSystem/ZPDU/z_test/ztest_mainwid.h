#ifndef ZTEST_MAINWID_H
#define ZTEST_MAINWID_H

#include <QWidget>

namespace Ui {
class ZTest_MainWid;
}

class ZTest_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_MainWid(QWidget *parent = 0);
    ~ZTest_MainWid();
protected:
    QString getName(int mode);
protected slots:
    void initFunSLot();

private:
    Ui::ZTest_MainWid *ui;
};

#endif // ZTEST_MAINWID_H
