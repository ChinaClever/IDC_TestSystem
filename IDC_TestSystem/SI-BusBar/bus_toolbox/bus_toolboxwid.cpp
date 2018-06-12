#include "bus_toolboxwid.h"
#include "ui_bus_toolboxwid.h"
#include <QGridLayout>

BUS_ToolBoxWid::BUS_ToolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_ToolBoxWid)
{
    ui->setupUi(this);

    initWid();
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(this);
    groupBox_background_icon(this);
}

BUS_ToolBoxWid::~BUS_ToolBoxWid()
{
    delete ui;
}


void BUS_ToolBoxWid::initWid()
{
    int page = 0;

    mSimulationToolWid = new BUS_SimulationToolWid(ui->toolBox->widget(page++));
    connect(mSimulationToolWid, SIGNAL(simulateSig(int)), this, SIGNAL(toolBoxSig(int)));

    mLogsToolWid = new BusLogsToolWid(ui->toolBox->widget(page++));
    connect(mLogsToolWid, SIGNAL(logsSig(int)), this, SIGNAL(toolBoxSig(int)));

    mSettingToolWid = new BUS_SettingToolWid(ui->toolBox->widget(page++));

}
