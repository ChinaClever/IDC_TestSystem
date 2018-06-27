#include "mpdurtutest_thresholditemwid.h"
#include "ui_mpdurtutest_thresholditemwid.h"
extern void com_setBackColour(const QString &,QWidget *target);

MpduRtuTest_ThresholdItemWid::MpduRtuTest_ThresholdItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_ThresholdItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    mRate = 1;
}

MpduRtuTest_ThresholdItemWid::~MpduRtuTest_ThresholdItemWid()
{
    delete ui;
}

QString MpduRtuTest_ThresholdItemWid::getStr(int mode)
{
    QString str;

    switch (mode) {
    case Mpdu_Rtu_Test_min: str = tr("最小值"); break;
    case Mpdu_Rtu_Test_crMin: str = tr("下限值"); break;
    case Mpdu_Rtu_Test_crMax: str = tr("上限值"); break;
    case Mpdu_Rtu_Test_max: str = tr("最大值"); break;
    default: break;
    }

    return str;
}

void MpduRtuTest_ThresholdItemWid::init(int id, int mode)
{
    QString str =getStr(mode);
    ui->checkBox->setText(tr(" %1 输出位电流%2").arg(id+1).arg(str));
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
        ret = ui->spinBox->value()*mRate;

    return ret;
}

void MpduRtuTest_ThresholdItemWid::on_spinBox_valueChanged(double arg1)
{
    ui->checkBox->setChecked(true);
}
