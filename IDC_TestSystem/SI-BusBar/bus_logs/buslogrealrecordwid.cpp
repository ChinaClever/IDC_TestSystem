/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "buslogrealrecordwid.h"

BusLogRealRecordWid::BusLogRealRecordWid(QWidget *parent) : LogComWid(parent)
{    
    setStretch();
}


BasicSql *BusLogRealRecordWid::getDb()
{
   return  BusDbRealRecords::bulid();
}


void BusLogRealRecordWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "BUS " + tr("历史纪录日志");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("母线")
             << tr("插接箱") << tr("回路") << tr("开关")
             << tr("电压") << tr("电流") << tr("视在功率")
             << tr("有功功率") << tr("功率因素") << tr("电能");
   model->setHeaders(mHeadList);
}
