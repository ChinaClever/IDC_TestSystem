#include "rset_envitemwid.h"
#include "ui_rset_envitemwid.h"

RSet_EnvItemWid::RSet_EnvItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_EnvItemWid)
{
    ui->setupUi(this);
}

RSet_EnvItemWid::~RSet_EnvItemWid()
{
    delete ui;
}
QString RSet_EnvItemWid::getTypeName(int type)
{
    QString str;
    switch (type) {
    case Rpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Rpdu_Rtu_Test_max: str += tr("最大值"); break;
//    case Rpdu_Rtu_Test_crMin: str += tr("下限值"); break;
//    case Rpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    default: break;
    }

    return str;
}

int RSet_EnvItemWid::getReg(int mode, int type)
{
    //int reg = R_RtuReg_TemMin;
    int reg = R_RtuReg_TemMin;
    if(mode) //reg = R_RtuReg_HumMin;
        reg = R_RtuReg_HumMin;

    switch (type) {
    case Rpdu_Rtu_Test_min:  break;
    case Rpdu_Rtu_Test_max: reg += 0x10; break;/*
    case Rpdu_Rtu_Test_crMin: reg += 0x200; break;
    case Rpdu_Rtu_Test_crMax: reg += 0x300; break;*/
    default: break;
    }

    return reg;
}


void RSet_EnvItemWid::initwid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2 , ui->widget_3, ui->widget_4};
    for(int i=0; i<4; ++i) {
        mWid[i] = new RSet_ThresholdItemWid(wid[i]);
        mWid[i]->initEnv(i, mode);
    }
    mReg  = getReg(mode, type);

    QString str = tr("温度");
    if(mode) str = tr("湿度");
    str += getTypeName(type);
    ui->label->setText(str);
}
