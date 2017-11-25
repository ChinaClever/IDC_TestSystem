#ifndef SIMAINWID_H
#define SIMAINWID_H

#include <QWidget>
#include "toolbox/sitoolboxwid.h"

namespace Ui {
class SIMainWid;
}

class SIMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit SIMainWid(QWidget *parent = 0);
    ~SIMainWid();

protected:

private slots:

private:
    Ui::SIMainWid *ui;

    SitoolBoxWid *mtoolBoxWid;

};

#endif // SIMAINWID_H
