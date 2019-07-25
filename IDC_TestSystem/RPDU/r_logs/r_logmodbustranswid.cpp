/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_logmodbustranswid.h"
#include "r_sql/r_dbmodbustrans.h"

R_LogModbusTransWid::R_LogModbusTransWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

BasicSql *R_LogModbusTransWid::getDb()
{
    return  R_DbModbusTrans::bulid();
}


void R_LogModbusTransWid::initTable()
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
