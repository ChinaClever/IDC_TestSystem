/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_logoutputrecordwid.h"
#include "r_sql/r_dboutputrecords.h"

R_LogOutputRecordWid::R_LogOutputRecordWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *R_LogOutputRecordWid::getDb()
{
   return  R_DbOutputRecords::bulid();
}


void R_LogOutputRecordWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "R-PDU " + tr("输出位历史纪录日志");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
             << tr("输出位") << tr("开关") << tr("开关")
             << tr("电压") << tr("电流") << tr("视在功率")
             << tr("有功功率") << tr("功率因数") << tr("电能");
   model->setHeaders(mHeadList);
   setColumnHidden(5);
}
