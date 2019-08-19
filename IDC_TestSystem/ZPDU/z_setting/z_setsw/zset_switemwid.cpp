#include "zset_switemwid.h"
#include "ui_zset_switemwid.h"

ZSet_SwItemWid::ZSet_SwItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_SwItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    ui->openRadio->setChecked(true);
}

ZSet_SwItemWid::~ZSet_SwItemWid()
{
    delete ui;
}


void ZSet_SwItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void ZSet_SwItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool ZSet_SwItemWid::select()
{
    return ui->checkBox->isChecked();
}

void ZSet_SwItemWid::setOpen(bool checked)
{
    ui->openRadio->setChecked(checked);
}

void ZSet_SwItemWid::setClose(bool checked)
{
     ui->closeRadio->setChecked(checked);
}

int ZSet_SwItemWid::status()
{
    int ret = 2;
    if(ui->openRadio->isChecked())
        ret = 1;
    return ret;
}
