#include "rset_eleitemwid.h"
#include "ui_rset_eleitemwid.h"

RSet_EleItemWid::RSet_EleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_EleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

RSet_EleItemWid::~RSet_EleItemWid()
{
    delete ui;
}
void RSet_EleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void RSet_EleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool RSet_EleItemWid::select()
{
    return ui->checkBox->isChecked();
}

void RSet_EleItemWid::setClean(bool checked)
{
    ui->cleanRadio->setChecked(checked);
}


int RSet_EleItemWid::status()
{
    int ret = 0;
    if(ui->cleanRadio->isChecked())
        ret = 1;
    return ret;
}



void RSet_EleItemWid::on_cleanRadio_clicked()
{
    ui->checkBox->setChecked(true);
}
