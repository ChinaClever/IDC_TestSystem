#include "mpdurtutest_switemwid.h"
#include "ui_mpdurtutest_switemwid.h"


MpduRtuTest_SwItemWid::MpduRtuTest_SwItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_SwItemWid)
{
    ui->setupUi(this);
    ui->openRadio->setChecked(true);
}

MpduRtuTest_SwItemWid::~MpduRtuTest_SwItemWid()
{
    delete ui;
}

void MpduRtuTest_SwItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MpduRtuTest_SwItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MpduRtuTest_SwItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MpduRtuTest_SwItemWid::setOpen(bool checked)
{
    ui->openRadio->setChecked(checked);
}

void MpduRtuTest_SwItemWid::setClose(bool checked)
{
     ui->closeRadio->setChecked(checked);
}

int MpduRtuTest_SwItemWid::status()
{
    int ret = 0;
    if(ui->openRadio->isChecked())
        ret = 1;
    return ret;
}
