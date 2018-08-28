#include "ztest_switemwid.h"
#include "ui_ztest_switemwid.h"

ZTest_SwItemWid::ZTest_SwItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_SwItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    ui->openRadio->setChecked(true);
}

ZTest_SwItemWid::~ZTest_SwItemWid()
{
    delete ui;
}


void ZTest_SwItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void ZTest_SwItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool ZTest_SwItemWid::select()
{
    return ui->checkBox->isChecked();
}

void ZTest_SwItemWid::setOpen(bool checked)
{
    ui->openRadio->setChecked(checked);
}

void ZTest_SwItemWid::setClose(bool checked)
{
     ui->closeRadio->setChecked(checked);
}

int ZTest_SwItemWid::status()
{
    int ret = 0;
    if(ui->openRadio->isChecked())
        ret = 1;
    return ret;
}
