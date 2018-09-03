#include "ztest_eleitemwid.h"
#include "ui_ztest_eleitemwid.h"

ZTest_EleItemWid::ZTest_EleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_EleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

ZTest_EleItemWid::~ZTest_EleItemWid()
{
    delete ui;
}
void ZTest_EleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void ZTest_EleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool ZTest_EleItemWid::select()
{
    return ui->checkBox->isChecked();
}

void ZTest_EleItemWid::setClean(bool checked)
{
    ui->cleanRadio->setChecked(checked);
}


int ZTest_EleItemWid::status()
{
    int ret = 0;
    if(ui->cleanRadio->isChecked())
        ret = 1;
    return ret;
}



void ZTest_EleItemWid::on_cleanRadio_clicked()
{
    ui->checkBox->setChecked(true);
}
