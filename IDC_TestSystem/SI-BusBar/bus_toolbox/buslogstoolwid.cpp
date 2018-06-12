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


void BusLogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(BUS_Log_Modbus);
}

void BusLogsToolWid::on_transBtn_clicked()
{
    emit logsSig(BUS_Log_Trans);
}

void BusLogsToolWid::on_envBtn_clicked()
{
     emit logsSig(BUS_Log_Env);
}

void BusLogsToolWid::on_recordBtn_clicked()
{
    emit logsSig(BUS_Log_Records);
}

void BusLogsToolWid::on_thresholdBtn_clicked()
{
    emit logsSig(BUS_Log_Threshold);
}

void BusLogsToolWid::on_alarmBtn_clicked()
{
    emit logsSig(BUS_Log_Alarm);
}
