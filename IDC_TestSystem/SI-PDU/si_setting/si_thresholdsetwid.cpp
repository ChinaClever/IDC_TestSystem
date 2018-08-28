/*
 * 阈值设置
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_thresholdsetwid.h"
#include "ui_si_thresholdsetwid.h"

SI_ThresholdSetWid::SI_ThresholdSetWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI_ThresholdSetWid)
{
    ui->setupUi(this);

    initWid();
}

SI_ThresholdSetWid::~SI_ThresholdSetWid()
{
    delete ui;
}

/**
 * @brief 初始化窗口
 */
void SI_ThresholdSetWid::initWid()
{
    mUnitSetWid[0] = new SI_UnitSetWid(ui->widget_1);
    mUnitSetWid[1] = new SI_UnitSetWid(ui->widget_2);
    mUnitSetWid[2] = new SI_UnitSetWid(ui->widget_3);

    for(int i=0; i<3; i++) {
        mUnitSetWid[i]->setHidden(true);
        connect(this, SIGNAL(updateSig(int)), mUnitSetWid[i], SLOT(updateSlot(int)));
    }
}

/**
 * @brief 获取单位
 * @param mode
 * @return
 */
QString SI_ThresholdSetWid::getStr(int mode)
{
    QString str, title;
    switch (mode) {
    case SI_SetMode_Vol: str = "V"; title = tr("电压"); break;
    case SI_SetMode_Cur: str = "A"; title = tr("电流"); break;
    case SI_SetMode_Tem: str = "℃"; title = tr("温度"); break;
    case SI_SetMode_Hum: str = "%"; title = tr("湿度"); break;
    default:
        break;
    }
    ui->titleLab->setText(title);    

    return str;
}

/**
 * @brief 获得倍玄
 * @param mode
 * @return
 */
double SI_ThresholdSetWid::getRate(int mode)
{
    double rate = 1;
    switch (mode) {
    case SI_SetMode_Vol: rate = COM_RATE_VOL; break;
    case SI_SetMode_Cur: rate = COM_RATE_CUR; break;
    case SI_SetMode_Tem: rate = COM_RATE_TEM; break;
    case SI_SetMode_Hum: rate = COM_RATE_HUM; break;
    default:
        break;
    }

    return rate;
}

/**
 * @brief S获得寄存器在址
 * @param mode
 * @return
 */
int SI_ThresholdSetWid::getReg(int mode)
{
    int ret = 1;
    switch (mode) {
    case SI_SetMode_Vol: ret = SI_MaxVol1_CMD; break;
    case SI_SetMode_Cur: ret = SI_MaxCur1_CMD; break;
    case SI_SetMode_Tem: ret = SI_MaxTem_CMD; break;
    case SI_SetMode_Hum: ret = SI_MaxHum_CMD; break;
    default:
        break;
    }

    return ret;
}

/**
 * @brief 获得相数
 * @param mode
 * @param data
 * @return
 */
int SI_ThresholdSetWid::getLine(int mode, SI_RtuRecvLine &data)
{
    int ret = 1;
    switch (mode) {
    case SI_SetMode_Vol: ret = data.lineNum; break;
    case SI_SetMode_Cur: ret = data.lineNum; break;
    case SI_SetMode_Tem: ret = 1; break;
    case SI_SetMode_Hum: ret = 1; break;
    default:
        break;
    }

    return ret;
}


SI_sDataUnit * SI_ThresholdSetWid::getUnit(int mode, SI_RtuRecvLine &data)
{
    SI_sDataUnit *unit;
    switch (mode) {
    case SI_SetMode_Vol: unit = &(data.vol); break;
    case SI_SetMode_Cur: unit = &(data.cur); break;
    case SI_SetMode_Tem: unit = &(data.tem); break;
    case SI_SetMode_Hum: unit = &(data.hum); break;
    default:
        break;
    }

    return unit;
}

/**
 * @brief 初始化
 * @param mode
 * @param data
 */
void SI_ThresholdSetWid::init(int mode, SI_RtuRecvLine &data)
{
    int line = getLine(mode, data);
    SI_sDataUnit *unit = getUnit(mode, data);
    double rate = getRate(mode);
    QString str = getStr(mode);
    int reg = getReg(mode);

    for(int i=0; i<3; ++i) {
        mUnitSetWid[i]->setHidden(true);
        mUnitSetWid[i]->init(unit, i, rate, str, reg);
        reg += 2;
    }

    for(int i=0; i<line; i++) {
        mUnitSetWid[i]->setHidden(false);
    }
}

