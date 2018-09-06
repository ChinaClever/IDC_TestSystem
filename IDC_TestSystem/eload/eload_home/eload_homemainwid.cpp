#include "eload_homemainwid.h"
#include "ui_eload_homemainwid.h"

ELoad_HomeMainWid::ELoad_HomeMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_HomeMainWid)
{
    ui->setupUi(this);

    mInputWid = new ELoad_InputHomeWid(ui->widget_1);
    mStatusWid = new ELoad_StatusHomeWid(ui->widget_2);
}

ELoad_HomeMainWid::~ELoad_HomeMainWid()
{
    delete ui;
}
