#ifndef IP_SIMULATIONTOOLWID_H
#define IP_SIMULATIONTOOLWID_H

#include "ip_settingtoolwid.h"

namespace Ui {
class IP_SimulationToolWid;
}

class IP_SimulationToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit IP_SimulationToolWid(QWidget *parent = 0);
    ~IP_SimulationToolWid();

signals:
    void simulateSig(int);

protected:
    void startSimulateTest();
    bool stopSimulateTest();

private slots:
    void on_mnTestBtn_clicked();
    void on_devBtn_clicked();
    void on_transBtn_clicked();
    void on_thresholdBtn_clicked();
    void on_envBtn_clicked();
    void on_settingBtn_clicked();

private:
    Ui::IP_SimulationToolWid *ui;
};

#endif // IP_SIMULATIONTOOLWID_H
