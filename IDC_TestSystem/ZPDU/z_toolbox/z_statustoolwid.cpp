#include "z_statustoolwid.h"
#include "ui_z_statustoolwid.h"

Z_StatusToolWid::Z_StatusToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Z_StatusToolWid)
{
    ui->setupUi(this);
}

Z_StatusToolWid::~Z_StatusToolWid()
{
    delete ui;
}


void Z_StatusToolWid::on_devBtn_clicked()
{
    emit widSig(Info_Line);
}

void Z_StatusToolWid::on_transBtn_clicked()
{
    emit widSig(Info_Trans);
}

void Z_StatusToolWid::on_thresholdBtn_clicked()
{
    emit widSig(Info_LineThreshold);
}

void Z_StatusToolWid::on_envBtn_clicked()
{
    emit widSig(Info_Env);
}

void Z_StatusToolWid::on_outputBtn_clicked()
{
    emit widSig(Info_Output);
}

void Z_StatusToolWid::on_outputThresholdBtn_clicked()
{
    emit widSig(Info_OutputThreshold);
}


void Z_StatusToolWid::on_loopBtn_clicked()
{
     emit widSig(Info_Loop);
}

void Z_StatusToolWid::on_loopThresholdBtn_clicked()
{
    emit widSig(Info_LoopThreshold);
}
