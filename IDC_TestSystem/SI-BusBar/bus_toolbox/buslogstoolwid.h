#ifndef BUSLOGSTOOLWID_H
#define BUSLOGSTOOLWID_H

#include <QWidget>

namespace Ui {
class BusLogsToolWid;
}

class BusLogsToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit BusLogsToolWid(QWidget *parent = 0);
    ~BusLogsToolWid();

private:
    Ui::BusLogsToolWid *ui;
};

#endif // BUSLOGSTOOLWID_H
