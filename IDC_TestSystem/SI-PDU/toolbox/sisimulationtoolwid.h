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
    void stopSimulateTest();

private slots:
    void on_mnTestBtn_clicked();

private:
    Ui::SiSimulationToolWid *ui;
};

#endif // SISIMULATIONTOOLWID_H
