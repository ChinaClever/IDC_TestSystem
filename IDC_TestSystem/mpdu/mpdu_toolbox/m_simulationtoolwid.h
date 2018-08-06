#ifndef M_SIMULATIONTOOLWID_H
#define M_SIMULATIONTOOLWID_H

#include "m_settingtoolwid.h"

namespace Ui {
class M_SimulationToolWid;
}

class M_SimulationToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit M_SimulationToolWid(QWidget *parent = 0);
    ~M_SimulationToolWid();

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
    Ui::M_SimulationToolWid *ui;
};

#endif // M_SIMULATIONTOOLWID_H
