#ifndef ELOAD_HOMEMAINWID_H
#define ELOAD_HOMEMAINWID_H

#include "eload_statushomewid.h"
#include "eload_inputhomewid.h"

namespace Ui {
class ELoad_HomeMainWid;
}

class ELoad_HomeMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_HomeMainWid(QWidget *parent = 0);
    ~ELoad_HomeMainWid();

private:
    Ui::ELoad_HomeMainWid *ui;

    ELoad_InputHomeWid *mInputWid;
    ELoad_StatusHomeWid *mStatusWid;
};

#endif // ELOAD_HOMEMAINWID_H
