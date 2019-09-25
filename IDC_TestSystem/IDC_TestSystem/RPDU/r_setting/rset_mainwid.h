#ifndef RSET_MAINWID_H
#define RSET_MAINWID_H

#include <QWidget>

namespace Ui {
class RSet_MainWid;
}

class RSet_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_MainWid(QWidget *parent = 0);
    ~RSet_MainWid();
protected:
    QString getName(int mode);
protected slots:
    void initFunSLot();

private:
    Ui::RSet_MainWid *ui;
};

#endif // RSET_MAINWID_H
