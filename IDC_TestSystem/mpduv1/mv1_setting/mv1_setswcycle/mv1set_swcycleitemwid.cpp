#include "mv1set_swcycleitemwid.h"
#include "ui_mv1set_swcycleitemwid.h"
MV1Set_SwCycleItemWid::MV1Set_SwCycleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1Set_SwCycleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

MV1Set_SwCycleItemWid::~MV1Set_SwCycleItemWid()
{
    delete ui;
}
void MV1Set_SwCycleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MV1Set_SwCycleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MV1Set_SwCycleItemWid::select()
{
    return ui->checkBox->isChecked();
}
