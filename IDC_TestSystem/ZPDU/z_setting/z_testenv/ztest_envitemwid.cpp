#include "ztest_envitemwid.h"
#include "ui_ztest_envitemwid.h"

ZTest_EnvItemWid::ZTest_EnvItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_EnvItemWid)
{
    ui->setupUi(this);
}

ZTest_EnvItemWid::~ZTest_EnvItemWid()
{
    delete ui;
}
QString ZTest_EnvItemWid::getTypeName(int type)
{
    QString str;
    switch (type) {
    case Zpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Zpdu_Rtu_Test_max: str += tr("最大值"); break;
    case Zpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Zpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    default: break;
    }

    return str;
}

int ZTest_EnvItemWid::getReg(int mode, int type)
{
    int reg = Z_RtuReg_TemMin;
    if(mode) reg = Z_RtuReg_HumMin;

    switch (type) {
    case Zpdu_Rtu_Test_min:  break;
    case Zpdu_Rtu_Test_max: reg += 0x100; break;
    case Zpdu_Rtu_Test_crMin: reg += 0x200; break;
    case Zpdu_Rtu_Test_crMax: reg += 0x300; break;
    default: break;
    }

    return reg;
}


void ZTest_EnvItemWid::initwid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new ZTest_ThresholdItemWid(wid[i]);
        mWid[i]->initEnv(i, mode);
    }
    mReg  = getReg(mode, type);

    QString str = tr("温度");
    if(mode) str = tr("湿度");
    str += getTypeName(type);
    ui->label->setText(str);
}
