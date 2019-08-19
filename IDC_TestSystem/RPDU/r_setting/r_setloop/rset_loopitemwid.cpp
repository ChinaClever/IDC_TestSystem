#include "rset_loopitemwid.h"
#include "ui_rset_loopitemwid.h"

RSet_LoopItemWid::RSet_LoopItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_LoopItemWid)
{
    ui->setupUi(this);
}

RSet_LoopItemWid::~RSet_LoopItemWid()
{
    delete ui;
}
QString RSet_LoopItemWid::getTypeName(int type)
{
    QString str;
    switch (type) {
    case Rpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Rpdu_Rtu_Test_max: str += tr("最大值"); break;
    case Rpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Rpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    default: break;
    }

    return str;
}

int RSet_LoopItemWid::getReg(int type)
{
//    int reg = R_RtuReg_LoopCurMin;
    int reg = 0X8000;

    switch (type) {
    case Rpdu_Rtu_Test_min: break;
    case Rpdu_Rtu_Test_max: reg += 0x100; break;
    case Rpdu_Rtu_Test_crMin: reg += 0x200; break;
    case Rpdu_Rtu_Test_crMax: reg += 0x300; break;
    default: break;
    }

    return reg;
}

void RSet_LoopItemWid::initwid(int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3,ui->widget_4, ui->widget_5, ui->widget_6};
    for(int i=0; i<6; ++i) {
        mWid[i] = new RSet_ThresholdItemWid(wid[i]);
        mWid[i]->initLoop(i);
    }
    mReg = getReg(type);

    QString str = tr("回路电流");
    str += getTypeName(type);
    ui->label->setText(str);
}
