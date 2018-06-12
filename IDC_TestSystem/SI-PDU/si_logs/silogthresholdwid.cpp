/*
 * SI 设备阈值纪录
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "silogthresholdwid.h"
#include "si_sql/sidbthresholds.h"

SiLogThresholdWid::SiLogThresholdWid(QWidget *parent) : LogComWid(parent)
{
     setStretch();
}


BasicSql *SiLogThresholdWid::getDb()
{
    return  SiDbThresholds::bulid();
}


void SiLogThresholdWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "SI " + tr("设备阈值纪录");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间")
              << tr("设备号") << tr("相数")
              << tr("电压") << tr("电压下限") << tr("电压上限")
              << tr("电流") << tr("电流下限") << tr("电流上限");
    model->setHeaders(mHeadList);
}
