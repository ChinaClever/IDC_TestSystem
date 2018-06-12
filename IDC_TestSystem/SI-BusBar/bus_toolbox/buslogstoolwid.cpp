#include "buslogstoolwid.h"
#include "ui_buslogstoolwid.h"

BusLogsToolWid::BusLogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BusLogsToolWid)
{
    ui->setupUi(this);
}

BusLogsToolWid::~BusLogsToolWid()
{
    delete ui;
}
