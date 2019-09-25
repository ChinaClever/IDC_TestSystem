#ifndef MSET_ELEITEMWID_H
#define MSET_ELEITEMWID_H

#include "../m_setline/mset_linewid.h"

namespace Ui {
class MSet_EleItemWid;
}

class MSet_EleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_EleItemWid(QWidget *parent = 0);
    ~MSet_EleItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setClean(bool checked);

    bool select();
    int status();
private slots:
    void on_cleanRadio_clicked();

private:
    Ui::MSet_EleItemWid *ui;
};

#endif // MSET_ELEITEMWID_H
