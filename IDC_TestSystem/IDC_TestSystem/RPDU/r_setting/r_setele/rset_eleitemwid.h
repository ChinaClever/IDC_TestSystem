#ifndef RSET_ELEITEMWID_H
#define RSET_ELEITEMWID_H

#include <QWidget>
#include "common.h"
namespace Ui {
class RSet_EleItemWid;
}

class RSet_EleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_EleItemWid(QWidget *parent = 0);
    ~RSet_EleItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setClean(bool checked);

    bool select();
    int status();


private slots:
    void on_cleanRadio_clicked();

private:
    Ui::RSet_EleItemWid *ui;
};

#endif // RSET_ELEITEMWID_H
