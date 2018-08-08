/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "buslogmodbuscmdwid.h"

BusLogModbusCmdWid::BusLogModbusCmdWid(QWidget *parent) : LogComWid(parent)
{

}


BasicSql *BusLogModbusCmdWid::getDb()
{
    return  BusDbModbusCmd::bulid();
}

void BusLogModbusCmdWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输错误日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("母线")<< tr("插接箱")<< tr("内容") ;
    model->setHeaders(mHeadList);
}
