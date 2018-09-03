#include "ztest_thresholditemwid.h"
#include "ui_ztest_thresholditemwid.h"

ZTest_ThresholdItemWid::ZTest_ThresholdItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_ThresholdItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    mRate = 1;
}

ZTest_ThresholdItemWid::~ZTest_ThresholdItemWid()
{
    delete ui;
}
QString ZTest_ThresholdItemWid::getStr(int mode)
{
    QString str=tr("电流");

    switch (mode) {
    case Zpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Zpdu_Rtu_Test_max: str += tr("最大值"); break;
    case Zpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Zpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    default: break;
    }

    return str;
}

void ZTest_ThresholdItemWid::initOutput(int id, int mode)
{
    QString str =getStr(mode);
    ui->checkBox->setText(tr(" %1 输出位%2").arg(id+1).arg(str));
}

void ZTest_ThresholdItemWid::initLine(int id, int mode)
{
    ui->checkBox->setText(tr(" L%1").arg(id+1));
    if(mode) ui->spinBox->setSuffix("V");
}
void ZTest_ThresholdItemWid::initLoop(int id)
{
    ui->checkBox->setText(tr(" C%1").arg(id+1));
}

void ZTest_ThresholdItemWid::initEnv(int id, int mode)
{
    QString name, str;
    if(mode) {
        name = tr("湿度");
        str = "%";
    } else {
        name = tr("温度");
        str = "℃";
    }

    ui->checkBox->setText(tr(" %1%2").arg(name).arg(id+1));
    ui->spinBox->setSuffix(str);
}

void ZTest_ThresholdItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool ZTest_ThresholdItemWid::select()
{
    return ui->checkBox->isChecked();
}

void ZTest_ThresholdItemWid::setValue(int value)
{
    ui->spinBox->setValue(value);
}


int ZTest_ThresholdItemWid::status()
{
    int ret = -1;
    if(ui->checkBox->isChecked())
        ret = ui->spinBox->value()*mRate;

    return ret;
}

void ZTest_ThresholdItemWid::on_spinBox_valueChanged(int arg1)
{
    ui->checkBox->setChecked(true);
}
