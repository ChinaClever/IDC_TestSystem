/*
 * SI 历史纪录日志
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "silogrealrecordwid.h"
#include "si_sql/sidbrealrecords.h"

SiLogRealRecordWid::SiLogRealRecordWid(QWidget *parent) : LogComWid(parent)
{
     setStretch();
}


BasicSql *SiLogRealRecordWid::getDb()
{
    return  SiDbRealRecords::bulid();
}


void SiLogRealRecordWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "SI " + tr("历史纪录日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
              << tr("相数") << tr("开关") << tr("开关")
              << tr("电压") << tr("电流") << tr("视在功率")
              << tr("有功功率") << tr("功率因素") << tr("电能");
    model->setHeaders(mHeadList);
}
