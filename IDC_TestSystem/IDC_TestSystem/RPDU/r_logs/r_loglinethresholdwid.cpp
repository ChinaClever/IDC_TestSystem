/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_loglinethresholdwid.h"
#include "r_sql/r_dblinethresholds.h"

R_LogLineThresholdWid::R_LogLineThresholdWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *R_LogLineThresholdWid::getDb()
{
   return  R_DbLineThresholds::bulid();
}


void R_LogLineThresholdWid::initTable()
{
   QString table = getDb()->tableName();
   this->refreshTable(table);

   mTableTile = "R-PDU " + tr("设备阈值纪录");
   setGroupBoxTitle(mTableTile);

   mHeadList.clear();
   mHeadList << tr("编号") << tr("日期") << tr("时间")
             << tr("设备号") << tr("相数")
             << tr("电压") << tr("电压下限") << tr("电压上限")
             << tr("电流") << tr("电流下限") << tr("电流上限");
   model->setHeaders(mHeadList);
}
