#include "buslogswid.h"
#include "ui_buslogswid.h"

BusLogsWid::BusLogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BusLogsWid)
{
    ui->setupUi(this);
}

BusLogsWid::~BusLogsWid()
{
    delete ui;
}
