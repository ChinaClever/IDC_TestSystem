#include "simainwid.h"
#include "ui_simainwid.h"
#include "si_simulate/si_simulatethread.h"


SIMainWid::SIMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SIMainWid)
{
    ui->setupUi(this);

    mtoolBoxWid = new SitoolBoxWid(ui->toolBoxWid);

    SI_SimulateThread *t = new SI_SimulateThread(this);
    t->startThread();
}

SIMainWid::~SIMainWid()
{
    delete ui;
}

