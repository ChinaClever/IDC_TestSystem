#ifndef MTEST_MAINWID_H
#define MTEST_MAINWID_H

#include <QWidget>

namespace Ui {
class MTest_MainWid;
}

class MTest_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_MainWid(QWidget *parent = 0);
    ~MTest_MainWid();

protected:
    QString getName(int mode);

protected slots:
    void initFunSLot();

private:
    Ui::MTest_MainWid *ui;
};

#endif // MTEST_MAINWID_H
