#include "testtoolwid.h"
#include "ui_testtoolwid.h"

TestToolWid::TestToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestToolWid)
{
    ui->setupUi(this);
}

TestToolWid::~TestToolWid()
{
    delete ui;
}



void TestToolWid::on_startBtn_clicked()
{
    ui->startBtn->setEnabled(false);
    ui->pauseBtn->setEnabled(true);
    ui->overBtn->setEnabled(true);
    emit simulateSig(Test_Start);
}

void TestToolWid::on_pauseBtn_clicked()
{
    ui->pauseBtn->setEnabled(false);
    ui->continueBtn->setEnabled(true);
    emit simulateSig(Test_Pause);
}

void TestToolWid::on_continueBtn_clicked()
{
    ui->continueBtn->setEnabled(false);
    ui->pauseBtn->setEnabled(true);
    emit simulateSig(Test_Continue);
}

void TestToolWid::on_overBtn_clicked()
{
    ui->overBtn->setEnabled(false);
    ui->continueBtn->setEnabled(false);
    ui->startBtn->setEnabled(true);
    emit simulateSig(Test_Over);
}

void TestToolWid::on_resultBtn_clicked()
{
    emit simulateSig(Test_Result);
}

void TestToolWid::on_testItemBtn_clicked()
{
    emit simulateSig(Test_Item);
}

void TestToolWid::on_testDataBtn_clicked()
{
    emit simulateSig(Test_Data);
}
