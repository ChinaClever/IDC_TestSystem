#include "mpdurtutest_thresholditemwid.h"
#include "ui_mpdurtutest_thresholditemwid.h"

MpduRtuTest_ThresholdItemWid::MpduRtuTest_ThresholdItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_ThresholdItemWid)
{
    ui->setupUi(this);
}

MpduRtuTest_ThresholdItemWid::~MpduRtuTest_ThresholdItemWid()
{
    delete ui;
}


void MpduRtuTest_ThresholdItemWid::init(int id, int mode)
{
    QString str = tr("小");
    if(mode) str = tr("大");

    ui->checkBox->setText(tr(" %1 输出位电流最%2值").arg(id+1).arg(str));
}


void MpduRtuTest_ThresholdItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MpduRtuTest_ThresholdItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MpduRtuTest_ThresholdItemWid::setValue(double value)
{
    ui->spinBox->setValue(value);
}


int MpduRtuTest_ThresholdItemWid::status()
{
    int ret = -1;
    if(ui->checkBox->isChecked())
        ret = ui->spinBox->value()*10;

    return ret;
}

void MpduRtuTest_ThresholdItemWid::on_spinBox_valueChanged(double arg1)
{
    ui->checkBox->setChecked(true);
}
