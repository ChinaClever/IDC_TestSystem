#include "mset_swcycleitemwid.h"
#include "ui_mset_swcycleitemwid.h"
MSet_SwCycleItemWid::MSet_SwCycleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_SwCycleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

MSet_SwCycleItemWid::~MSet_SwCycleItemWid()
{
    delete ui;
}
void MSet_SwCycleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MSet_SwCycleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MSet_SwCycleItemWid::select()
{
    return ui->checkBox->isChecked();
}
