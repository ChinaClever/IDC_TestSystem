#ifndef SIMAINWID_H
#define SIMAINWID_H

#include <QWidget>
#include "toolbox/sitoolboxwid.h"
#include "si_simulate/si_simulatethread.h"
#include "si_logs/silogmodbuscmdwid.h"
#include "si_simulate/sienvtablewid.h"

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
    void initWid();

private slots:
    void toolBoxSlot(int);

private:
    Ui::SIMainWid *ui;

    SitoolBoxWid *mtoolBoxWid;
    SI_SimulateThread *mSimulateThread;
    SiEnvTableWid *mEnvTableWid;

    SiLogModbusCmdWid *mLogModbusCmdWid;
};

#endif // SIMAINWID_H
