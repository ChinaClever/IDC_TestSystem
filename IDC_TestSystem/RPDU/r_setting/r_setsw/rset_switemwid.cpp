#include "rset_switemwid.h"
#include "ui_rset_switemwid.h"

RSet_SwItemWid::RSet_SwItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_SwItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    ui->openRadio->setChecked(true);
}

RSet_SwItemWid::~RSet_SwItemWid()
{
    delete ui;
}


void RSet_SwItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void RSet_SwItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool RSet_SwItemWid::select()
{
    return ui->checkBox->isChecked();
}

void RSet_SwItemWid::setOpen(bool checked)
{
    ui->openRadio->setChecked(checked);
}

void RSet_SwItemWid::setClose(bool checked)
{
     ui->closeRadio->setChecked(checked);
}

int RSet_SwItemWid::status()
{
    int ret = 0;
    if(ui->openRadio->isChecked())
        ret = 1;
    return ret;
}
