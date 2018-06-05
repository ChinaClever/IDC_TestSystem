#include "bus_toolboxwid.h"
#include "ui_bus_toolboxwid.h"
#include <QGridLayout>

BUS_ToolBoxWid::BUS_ToolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_ToolBoxWid)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(this);
    groupBox_background_icon(this);
}

BUS_ToolBoxWid::~BUS_ToolBoxWid()
{
    delete ui;
}
