#include "zset_swcycleitemwid.h"
#include "ui_zset_swcycleitemwid.h"

ZSet_SwCycleItemWid::ZSet_SwCycleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_SwCycleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

ZSet_SwCycleItemWid::~ZSet_SwCycleItemWid()
{
    delete ui;
}

void ZSet_SwCycleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void ZSet_SwCycleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool ZSet_SwCycleItemWid::select()
{
    return ui->checkBox->isChecked();
}
