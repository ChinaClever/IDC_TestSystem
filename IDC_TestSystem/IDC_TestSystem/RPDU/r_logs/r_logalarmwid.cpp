/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_logalarmwid.h"
#include "r_sql/r_dbalarm.h"

R_LogAlarmWid::R_LogAlarmWid(QWidget *parent) : LogComWid(parent)
{

}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *R_LogAlarmWid::getDb()
{
    return  R_DbAlarm::bulid();
}

/**
 * @brief 初始化表格
 */
void R_LogAlarmWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "R-PDU " + tr("报警日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
              << tr("相数") << tr("项目") << tr("内容");
    model->setHeaders(mHeadList);
}
