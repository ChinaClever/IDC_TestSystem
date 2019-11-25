/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_loglinerecordwid.h"
#include "z_sql/z_dblinerecords.h"

Z_LogLineRecordWid::Z_LogLineRecordWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *Z_LogLineRecordWid::getDb()
{
   return  Z_DbLineRecords::bulid();
}


void Z_LogLineRecordWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "Z-PDU " + tr("历史纪录日志");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
             << tr("相数") << tr("开关") << tr("开关")
             << tr("电压") << tr("电流") << tr("视在功率")
             << tr("有功功率") << tr("功率因数") << tr("电能");
   model->setHeaders(mHeadList);
   setColumnHidden(5);
}
