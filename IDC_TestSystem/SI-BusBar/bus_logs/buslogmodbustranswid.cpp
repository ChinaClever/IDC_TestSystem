/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "buslogmodbustranswid.h"

BusLogModbusTransWid::BusLogModbusTransWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

BasicSql *BusLogModbusTransWid::getDb()
{
    return  BusDbModbusTrans::bulid();
}


void BusLogModbusTransWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输统计日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("母线") << tr("插接箱")
                 << tr("状态") << tr("总次数") << tr("成功次数") << tr("失败次数");
    model->setHeaders(mHeadList);
}
