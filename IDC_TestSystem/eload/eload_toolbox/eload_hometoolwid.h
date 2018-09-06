#ifndef ELOAD_HOMETOOLWID_H
#define ELOAD_HOMETOOLWID_H

#include "eload_com/eload_configfile.h"

namespace Ui {
class ELoad_HomeToolWid;
}

class ELoad_HomeToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_HomeToolWid(QWidget *parent = 0);
    ~ELoad_HomeToolWid();

signals:
    void toolSig(int);

private slots:
    void on_homeBtn_clicked();

private:
    Ui::ELoad_HomeToolWid *ui;
};

#endif // ELOAD_HOMETOOLWID_H
