/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_loglooprecordwid.h"
#include "r_sql/r_dblooprecords.h"

R_LogLoopRecordWid::R_LogLoopRecordWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *R_LogLoopRecordWid::getDb()
{
   return  R_DbLoopRecords::bulid();
}


void R_LogLoopRecordWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "R-PDU " + tr("回路纪录日志");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
             << tr("回路") << tr("开关") << tr("开关")
             << tr("电压") << tr("电流") << tr("视在功率")
             << tr("有功功率") << tr("功率因素") << tr("电能");
   model->setHeaders(mHeadList);
   setColumnHidden(5);
   setColumnHidden(10);
   setColumnHidden(11);
}
