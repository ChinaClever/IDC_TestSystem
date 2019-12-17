#ifndef MV1SET_ELEITEMWID_H
#define MV1SET_ELEITEMWID_H

#include "../mv1_setline/mv1set_linewid.h"

namespace Ui {
class MV1Set_EleItemWid;
}

class MV1Set_EleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_EleItemWid(QWidget *parent = 0);
    ~MV1Set_EleItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setClean(bool checked);

    bool select();
    int status();
private slots:
    void on_cleanRadio_clicked();

private:
    Ui::MV1Set_EleItemWid *ui;
};

#endif // MV1SET_ELEITEMWID_H
