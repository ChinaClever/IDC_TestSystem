#include "eload_loglinerecordwid.h"
#include "ELoad_sql/ELoad_dblinerecords.h"

ELoad_LogLineRecordWid::ELoad_LogLineRecordWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *ELoad_LogLineRecordWid::getDb()
{
   return  ELoad_DbLineRecords::bulid();
}


void ELoad_LogLineRecordWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "ELoad " + tr("历史纪录日志");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
             << tr("相数") << tr("开关") << tr("开关")
             << tr("电压") << tr("电流") << tr("视在功率")
             << tr("有功功率") << tr("功率因素") << tr("电能");
   model->setHeaders(mHeadList);
   setColumnHidden(5);
}
