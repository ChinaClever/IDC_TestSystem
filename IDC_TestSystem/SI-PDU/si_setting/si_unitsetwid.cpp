/*
 * 阈值设置 组成部分
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_unitsetwid.h"
#include "ui_si_unitsetwid.h"

SI_UnitSetWid::SI_UnitSetWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI_UnitSetWid)
{
    ui->setupUi(this);
    mLine = 0;
    mRate = 1;
    mAddr = 1;
}

SI_UnitSetWid::~SI_UnitSetWid()
{
    delete ui;
}

/**
 * @brief 初始化
 * @param unit
 * @param line
 * @param rate
 * @param str
 * @param reg
 */
void SI_UnitSetWid::init(SI_sDataUnit *unit, int line, double rate, const QString &str, int reg)
{
    mUnit = unit;
    mLine = line;
    mRate = rate;
    mReg = reg;

    ui->spinBox->setSuffix(str);
    ui->maxSpinBox->setSuffix(str);
    ui->minSpinBox->setSuffix(str);
}

/**
 * @brief 数据更新
 * @param line
 */
void SI_UnitSetWid::updateData(int line)
{
    double value = mUnit->value[line] / mRate;
    ui->spinBox->setValue(value);

    int max = mUnit->max[line];
    ui->maxSpinBox->setValue(max);

    int min = mUnit->min[line];
    ui->minSpinBox->setValue(min);

    QString str = "color:black;";
    if((value > max) || (value < min))
        str = "color:red;";
    ui->spinBox->setStyleSheet(str);
}

void SI_UnitSetWid::updateSlot(int addr)
{
    mAddr = addr;
    updateData(mLine);
}

/**
 * @brief 修改数据
 * @param addr
 * @param reg
 * @param value
 */
void SI_UnitSetWid::setData(int addr, int reg, int value)
{
    bool ret =SI_RtuThread::bulid()->sentSetCmd(addr,reg, value, 20);
    if(ret) {
        InfoMsgBox box(this, tr("修改成功！！"));
    } else {
        CriticalMsgBox box(this, tr("修改失败！！！"));
    }
}

void SI_UnitSetWid::on_maxBtn_clicked()
{
    int value = ui->maxSpinBox->value();
    setData(mAddr, mReg, value);
}

void SI_UnitSetWid::on_minBtn_clicked()
{
    int value = ui->minSpinBox->value();
    setData(mAddr, mReg+1, value);
}
