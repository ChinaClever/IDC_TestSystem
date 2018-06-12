#include "bus_simulationtoolwid.h"
#include "ui_bus_simulationtoolwid.h"

BUS_SimulationToolWid::BUS_SimulationToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_SimulationToolWid)
{
    ui->setupUi(this);
}

BUS_SimulationToolWid::~BUS_SimulationToolWid()
{
    delete ui;
}

void BUS_SimulationToolWid::on_busBtn_clicked()
{
    emit simulateSig(BUS_Info_Bus);
}

void BUS_SimulationToolWid::on_boxBtn_clicked()
{
    emit simulateSig(BUS_Info_Box);
}

void BUS_SimulationToolWid::on_loopBtn_clicked()
{
    emit simulateSig(BUS_Info_Loop);
}

void BUS_SimulationToolWid::on_transBtn_clicked()
{
    emit simulateSig(BUS_Info_Trans);
}

void BUS_SimulationToolWid::on_thresholdBtn_clicked()
{
    emit simulateSig(BUS_Info_Threshold);
}

void BUS_SimulationToolWid::on_envBtn_clicked()
{
    emit simulateSig(BUS_Info_Env);
}
