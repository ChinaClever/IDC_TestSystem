#ifndef BUS_SIMULATIONTOOLWID_H
#define BUS_SIMULATIONTOOLWID_H

#include "bus_settingtoolwid.h"

namespace Ui {
class BUS_SimulationToolWid;
}

class BUS_SimulationToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_SimulationToolWid(QWidget *parent = 0);
    ~BUS_SimulationToolWid();

signals:
    void simulateSig(int);

private slots:
    void on_busBtn_clicked();

    void on_boxBtn_clicked();

    void on_loopBtn_clicked();

    void on_transBtn_clicked();

    void on_thresholdBtn_clicked();

    void on_envBtn_clicked();

private:
    Ui::BUS_SimulationToolWid *ui;
};

#endif // BUS_SIMULATIONTOOLWID_H
