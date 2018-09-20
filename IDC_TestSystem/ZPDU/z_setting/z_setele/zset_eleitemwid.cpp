#include "zset_eleitemwid.h"
#include "ui_zset_eleitemwid.h"

ZSet_EleItemWid::ZSet_EleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_EleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

ZSet_EleItemWid::~ZSet_EleItemWid()
{
    delete ui;
}
void ZSet_EleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void ZSet_EleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool ZSet_EleItemWid::select()
{
    return ui->checkBox->isChecked();
}

void ZSet_EleItemWid::setClean(bool checked)
{
    ui->cleanRadio->setChecked(checked);
}


int ZSet_EleItemWid::status()
{
    int ret = 0;
    if(ui->cleanRadio->isChecked())
        ret = 1;
    return ret;
}



void ZSet_EleItemWid::on_cleanRadio_clicked()
{
    ui->checkBox->setChecked(true);
}
