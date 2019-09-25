/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_loglinerecordwid.h"
#include "m_sql/m_dblinerecords.h"

M_LogLineRecordWid::M_LogLineRecordWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *M_LogLineRecordWid::getDb()
{
   return  M_DbLineRecords::bulid();
}


void M_LogLineRecordWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "M-PDU " + tr("历史纪录日志");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
             << tr("相数") << tr("开关") << tr("开关")
             << tr("电压") << tr("电流") << tr("视在功率")
             << tr("有功功率") << tr("功率因素") << tr("电能");
   model->setHeaders(mHeadList);
   setColumnHidden(5);
}

