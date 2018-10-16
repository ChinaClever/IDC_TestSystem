#include "testtoolwid.h"
#include "ui_testtoolwid.h"

TestToolWid::TestToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

TestToolWid::~TestToolWid()
{
    delete ui;
}



void TestToolWid::on_startBtn_clicked()
{
    emit simulateSig(Test_Start);
}

void TestToolWid::on_pauseBtn_clicked()
{
    emit simulateSig(Test_Pause);
}

void TestToolWid::on_continueBtn_clicked()
{
    emit simulateSig(Test_Continue);
}

void TestToolWid::on_overBtn_clicked()
{
    emit simulateSig(Test_Over);
}

void TestToolWid::on_resultBtn_clicked()
{
    emit simulateSig(Test_Result_Wid);
}

void TestToolWid::on_testItemBtn_clicked()
{
    emit simulateSig(Test_Items_Wid);
}

void TestToolWid::on_testDataBtn_clicked()
{
    emit simulateSig(Test_Datas_Wid);
}
