/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_logmodbuscmdwid.h"
#include "r_sql/r_dbmodbuscmd.h"

R_LogModbusCmdWid::R_LogModbusCmdWid(QWidget *parent) : LogComWid(parent)
{

}

BasicSql *R_LogModbusCmdWid::getDb()
{
    return  R_DbModbusCmd::bulid();
}

void R_LogModbusCmdWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输错误日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")<< tr("内容") ;
    model->setHeaders(mHeadList);
}
