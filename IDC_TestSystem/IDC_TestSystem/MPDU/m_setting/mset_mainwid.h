#ifndef MSET_MAINWID_H
#define MSET_MAINWID_H

#include <QWidget>

namespace Ui {
class MSet_MainWid;
}

class MSet_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_MainWid(QWidget *parent = 0);
    ~MSet_MainWid();

protected:
    QString getName(int mode);

protected slots:
    void initFunSLot();

private:
    Ui::MSet_MainWid *ui;
};

#endif // MSET_MAINWID_H
