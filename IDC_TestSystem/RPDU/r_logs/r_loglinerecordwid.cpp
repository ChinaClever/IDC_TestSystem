/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_loglinerecordwid.h"
#include "r_sql/r_dblinerecords.h"

R_LogLineRecordWid::R_LogLineRecordWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *R_LogLineRecordWid::getDb()
{
   return  R_DbLineRecords::bulid();
}


void R_LogLineRecordWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "R-PDU " + tr("历史纪录日志");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
             << tr("相数") << tr("开关") << tr("开关")
             << tr("电压") << tr("电流") << tr("视在功率")
             << tr("有功功率") << tr("功率因数") << tr("电能");
   model->setHeaders(mHeadList);
   setColumnHidden(5);
}
