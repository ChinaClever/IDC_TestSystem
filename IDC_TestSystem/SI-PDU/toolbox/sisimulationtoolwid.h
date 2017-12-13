#ifndef SISIMULATIONTOOLWID_H
#define SISIMULATIONTOOLWID_H

#include <QWidget>

namespace Ui {
class SiSimulationToolWid;
}

class SiSimulationToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit SiSimulationToolWid(QWidget *parent = 0);
    ~SiSimulationToolWid();

signals:
    void simulateSig(int);

protected:
    void startSimulateTest();
    bool stopSimulateTest();

private slots:
    void on_mnTestBtn_clicked();

    void on_envBtn_clicked();

    void on_thresholdBtn_clicked();

    void on_transBtn_clicked();

    void on_realBtn_clicked();

    void on_settingBtn_clicked();

private:
    Ui::SiSimulationToolWid *ui;
};

#endif // SISIMULATIONTOOLWID_H
