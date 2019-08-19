#include "rset_lineitemwid.h"
#include "ui_rset_lineitemwid.h"

RSet_LineItemWid::RSet_LineItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_LineItemWid)
{
    ui->setupUi(this);
}

RSet_LineItemWid::~RSet_LineItemWid()
{
    delete ui;
}
QString RSet_LineItemWid::getTypeName(int type)
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

int RSet_LineItemWid::getReg(int mode, int type)
{
    //    int reg = R_RtuReg_LineCurMin;
    //    if(mode) reg = R_RtuReg_LineVolMin;
    int reg = R_RtuReg_LineCurMin;
    if(mode) reg = R_RtuReg_LineVolMin;
    mMode = mode;

    switch (type) {
    case Rpdu_Rtu_Test_min:  break;
    case Rpdu_Rtu_Test_max: reg += 0x3; break;
//    case Rpdu_Rtu_Test_crMin: reg += 0x200; break;
//    case Rpdu_Rtu_Test_crMax: reg += 0x300; break;
    default: break;
    }

    return reg;
}


void RSet_LineItemWid::initwid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3};
    for(int i=0; i<3; ++i) {
        mWid[i] = new RSet_ThresholdItemWid(wid[i]);
        mWid[i]->initLine(i, mode);
    }
    mReg  = getReg(mode, type);

    QString str = tr("相电流");
    if(mode) str = tr("相电压");
    str += getTypeName(type);
    ui->label->setText(str);
}
