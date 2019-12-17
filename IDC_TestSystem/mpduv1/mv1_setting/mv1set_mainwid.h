#ifndef MV1SET_MAINWID_H
#define MV1SET_MAINWID_H

#include <QWidget>

namespace Ui {
class MV1Set_MainWid;
}

class MV1Set_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_MainWid(QWidget *parent = 0);
    ~MV1Set_MainWid();

protected:
    QString getName(int mode);

protected slots:
    void initFunSLot();

private:
    Ui::MV1Set_MainWid *ui;
};

#endif // MV1SET_MAINWID_H
