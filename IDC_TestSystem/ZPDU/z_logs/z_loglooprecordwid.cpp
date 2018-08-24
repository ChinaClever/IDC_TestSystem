#include "z_loglooprecordwid.h"
#include "z_sql/z_dblooprecords.h"

Z_LogLoopRecordWid::Z_LogLoopRecordWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *Z_LogLoopRecordWid::getDb()
{
   return  Z_DbLoopRecords::bulid();
}


void Z_LogLoopRecordWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "Z-PDU " + tr("回路纪录日志");
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
