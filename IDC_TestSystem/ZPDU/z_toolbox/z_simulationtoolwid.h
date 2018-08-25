#ifndef Z_SIMULATIONTOOLWID_H
#define Z_SIMULATIONTOOLWID_H

#include "z_com/z_configfile.h"

namespace Ui {
class Z_SimulationToolWid;
}

class Z_SimulationToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit Z_SimulationToolWid(QWidget *parent = 0);
    ~Z_SimulationToolWid();

signals:
    void simulateSig(int);

protected:
    void startSimulateTest();
    bool stopSimulateTest();

private slots:
    void on_mnTestBtn_clicked();
    void on_devBtn_clicked();
    void on_loopBtn_clicked();
    void on_outputBtn_clicked();
    void on_transBtn_clicked();
    void on_thresholdBtn_clicked();
    void on_loopThresholdBtn_clicked();
    void on_outputThresholdBtn_clicked();
    void on_envBtn_clicked();
    void on_settingBtn_clicked();

private:
    Ui::Z_SimulationToolWid *ui;
};

#endif // Z_SIMULATIONTOOLWID_H
