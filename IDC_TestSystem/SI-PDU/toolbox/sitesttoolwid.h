#ifndef SITESTTOOLWID_H
#define SITESTTOOLWID_H

#include <QWidget>

namespace Ui {
class SiTestToolWid;
}

class SiTestToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit SiTestToolWid(QWidget *parent = 0);
    ~SiTestToolWid();

private:
    Ui::SiTestToolWid *ui;
};

#endif // SITESTTOOLWID_H
