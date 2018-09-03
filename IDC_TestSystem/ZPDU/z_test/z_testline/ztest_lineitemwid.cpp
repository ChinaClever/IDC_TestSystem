#include "ztest_lineitemwid.h"
#include "ui_ztest_lineitemwid.h"

ZTest_LineItemWid::ZTest_LineItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_LineItemWid)
{
    ui->setupUi(this);
}

ZTest_LineItemWid::~ZTest_LineItemWid()
{
    delete ui;
}
QString ZTest_LineItemWid::getTypeName(int type)
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

int ZTest_LineItemWid::getReg(int mode, int type)
{
    int reg = Z_RtuReg_LineCurMin;
    if(mode) reg = Z_RtuReg_LineVolMin;

    switch (type) {
    case Zpdu_Rtu_Test_min:  break;
    case Zpdu_Rtu_Test_max: reg += 0x100; break;
    case Zpdu_Rtu_Test_crMin: reg += 0x200; break;
    case Zpdu_Rtu_Test_crMax: reg += 0x300; break;
    default: break;
    }

    return reg;
}


void ZTest_LineItemWid::initwid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3};
    for(int i=0; i<3; ++i) {
        mWid[i] = new ZTest_ThresholdItemWid(wid[i]);
        mWid[i]->initLine(i, mode);
    }
    mReg  = getReg(mode, type);

    QString str = tr("相电流");
    if(mode) str = tr("相电压");
    str += getTypeName(type);
    ui->label->setText(str);
}
