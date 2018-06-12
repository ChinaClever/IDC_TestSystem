#include "buslogthresholdwid.h"

BusLogThresholdWid::BusLogThresholdWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *BusLogThresholdWid::getDb()
{
   return  BusDbThresholds::bulid();
}


void BusLogThresholdWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "Bus " + tr("设备阈值纪录");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间")
             << tr("母线")<< tr("插接箱") << tr("回路")
             << tr("电压") << tr("电压下限") << tr("电压上限")
             << tr("电流") << tr("电流下限") << tr("电流上限");
   model->setHeaders(mHeadList);
}
