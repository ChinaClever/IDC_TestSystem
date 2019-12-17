/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_logmodbustranswid.h"
#include "mv1_sql/mv1_dbmodbustrans.h"

MV1_LogModbusTransWid::MV1_LogModbusTransWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

BasicSql *MV1_LogModbusTransWid::getDb()
{
    return  MV1_DbModbusTrans::bulid();
}


void MV1_LogModbusTransWid::initTable()
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


