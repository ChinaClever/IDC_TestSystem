/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_loglinethresholdwid.h"
#include "mv1_sql/mv1_dblinethresholds.h"

MV1_LogLineThresholdWid::MV1_LogLineThresholdWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *MV1_LogLineThresholdWid::getDb()
{
   return  MV1_DbLineThresholds::bulid();
}


void MV1_LogLineThresholdWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "MPDUV1 " + tr("设备阈值纪录");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间")
             << tr("设备号") << tr("相数")
             << tr("电压") << tr("电压下限") << tr("电压上限")
             << tr("电流") << tr("电流下限") << tr("电流上限");
   model->setHeaders(mHeadList);
}

