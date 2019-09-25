#include "rset_swcycleitemwid.h"
#include "ui_rset_swcycleitemwid.h"

RSet_SwCycleItemWid::RSet_SwCycleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_SwCycleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

RSet_SwCycleItemWid::~RSet_SwCycleItemWid()
{
    delete ui;
}

void RSet_SwCycleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void RSet_SwCycleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool RSet_SwCycleItemWid::select()
{
    return ui->checkBox->isChecked();
}
