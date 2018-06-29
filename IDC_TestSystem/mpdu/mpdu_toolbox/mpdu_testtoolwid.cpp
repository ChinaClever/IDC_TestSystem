#include "mpdu_testtoolwid.h"
#include "ui_mpdu_testtoolwid.h"

Mpdu_TestToolWid::Mpdu_TestToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mpdu_TestToolWid)
{
    ui->setupUi(this);
}

Mpdu_TestToolWid::~Mpdu_TestToolWid()
{
    delete ui;
}

void Mpdu_TestToolWid::on_serialBtn_clicked()
{

}
