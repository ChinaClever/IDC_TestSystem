#include "silogstoolwid.h"
#include "ui_silogstoolwid.h"
#include "si_com/siconfigfile.h"

SiLogsToolWid::SiLogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiLogsToolWid)
{
    ui->setupUi(this);
}

SiLogsToolWid::~SiLogsToolWid()
{
    delete ui;
}

void SiLogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(SI_Log_Modbus);
}
