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
