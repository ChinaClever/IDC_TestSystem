/*
 * Modbus传输统计日志
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "silogmodbustranswid.h"
#include "si_sql/sidbmodbustrans.h"

SiLogModbusTransWid::SiLogModbusTransWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

BasicSql *SiLogModbusTransWid::getDb()
{
    return  SiDbModbusTrans::bulid();
}


void SiLogModbusTransWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输统计日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
                 << tr("状态") << tr("总次数") << tr("成功次数") << tr("失败次数");
    model->setHeaders(mHeadList);
}

