#include "ip_simulatewid.h"
#include "ui_ip_simulatewid.h"

IP_SimulateWid::IP_SimulateWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IP_SimulateWid)
{
    ui->setupUi(this);
}

IP_SimulateWid::~IP_SimulateWid()
{
    delete ui;
}
