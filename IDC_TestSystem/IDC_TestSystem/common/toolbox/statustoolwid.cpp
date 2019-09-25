#include "statustoolwid.h"
#include "ui_statustoolwid.h"

StatusToolWid::StatusToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

StatusToolWid::~StatusToolWid()
{
    delete ui;
}

void StatusToolWid::mpdu()
{
    ui->loopBtn->setHidden(true);
    ui->loopThresholdBtn->setHidden(true);
}

void StatusToolWid::sipdu()
{
    mpdu();
    ui->outputBtn->setHidden(true);
    ui->outputThresholdBtn->setHidden(true);
}

void StatusToolWid::on_devBtn_clicked()
{
    emit widSig(Info_Line);
}

void StatusToolWid::on_transBtn_clicked()
{
    emit widSig(Info_Trans);
}

void StatusToolWid::on_thresholdBtn_clicked()
{
    emit widSig(Info_LineThreshold);
}

void StatusToolWid::on_envBtn_clicked()
{
    emit widSig(Info_Env);
}

void StatusToolWid::on_outputBtn_clicked()
{
    emit widSig(Info_Output);
}

void StatusToolWid::on_outputThresholdBtn_clicked()
{
    emit widSig(Info_OutputThreshold);
}


void StatusToolWid::on_loopBtn_clicked()
{
    emit widSig(Info_Loop);
}

void StatusToolWid::on_loopThresholdBtn_clicked()
{
    emit widSig(Info_LoopThreshold);
}
