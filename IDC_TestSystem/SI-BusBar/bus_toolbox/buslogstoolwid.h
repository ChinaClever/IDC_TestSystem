#ifndef BUSLOGSTOOLWID_H
#define BUSLOGSTOOLWID_H

#include "bus_simulationtoolwid.h"

namespace Ui {
class BusLogsToolWid;
}

class BusLogsToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit BusLogsToolWid(QWidget *parent = 0);
    ~BusLogsToolWid();

signals:
    void logsSig(int);

private slots:
    void on_modbusBtn_clicked();

    void on_transBtn_clicked();

    void on_envBtn_clicked();

    void on_recordBtn_clicked();

    void on_thresholdBtn_clicked();

    void on_alarmBtn_clicked();

private:
    Ui::BusLogsToolWid *ui;
};

#endif // BUSLOGSTOOLWID_H
