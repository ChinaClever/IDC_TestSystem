/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_logmodbuscmdwid.h"
#include "z_sql/z_dbmodbuscmd.h"

Z_LogModbusCmdWid::Z_LogModbusCmdWid(QWidget *parent) : LogComWid(parent)
{

}

BasicSql *Z_LogModbusCmdWid::getDb()
{
    return  Z_DbModbusCmd::bulid();
}

void Z_LogModbusCmdWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输错误日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")<< tr("内容") ;
    model->setHeaders(mHeadList);
}
