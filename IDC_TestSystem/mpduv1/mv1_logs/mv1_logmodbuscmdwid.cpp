/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_logmodbuscmdwid.h"
#include "mv1_sql/mv1_dbmodbuscmd.h"

MV1_LogModbusCmdWid::MV1_LogModbusCmdWid(QWidget *parent) : LogComWid(parent)
{

}

BasicSql *MV1_LogModbusCmdWid::getDb()
{
    return  MV1_DbModbusCmd::bulid();
}

void MV1_LogModbusCmdWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输错误日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")<< tr("内容") ;
    model->setHeaders(mHeadList);
}
