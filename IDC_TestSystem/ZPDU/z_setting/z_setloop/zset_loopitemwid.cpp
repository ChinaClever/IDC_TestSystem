#include "zset_loopitemwid.h"
#include "ui_zset_loopitemwid.h"

ZSet_LoopItemWid::ZSet_LoopItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_LoopItemWid)
{
    ui->setupUi(this);
}

ZSet_LoopItemWid::~ZSet_LoopItemWid()
{
    delete ui;
}
QString ZSet_LoopItemWid::getTypeName(int type)
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

int ZSet_LoopItemWid::getReg(int type)
{
    int reg = Z_RtuReg_LoopCurMin;

    switch (type) {
    case Zpdu_Rtu_Test_min: break;
    case Zpdu_Rtu_Test_max: reg += 0x100; break;
    case Zpdu_Rtu_Test_crMin: reg += 0x200; break;
    case Zpdu_Rtu_Test_crMax: reg += 0x300; break;
    default: break;
    }

    return reg;
}


void ZSet_LoopItemWid::initwid(int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3,ui->widget_4, ui->widget_5, ui->widget_6};
    for(int i=0; i<6; ++i) {
        mWid[i] = new ZSet_ThresholdItemWid(wid[i]);
        mWid[i]->initLoop(i);
    }
    mReg  = getReg(type);

    QString str = tr("回路电流");
    str += getTypeName(type);
    ui->label->setText(str);
}
