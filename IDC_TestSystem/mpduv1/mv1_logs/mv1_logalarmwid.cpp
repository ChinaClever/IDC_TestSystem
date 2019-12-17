/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_logalarmwid.h"
#include "mv1_sql/mv1_dbalarm.h"

MV1_LogAlarmWid::MV1_LogAlarmWid(QWidget *parent) : LogComWid(parent)
{

}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *MV1_LogAlarmWid::getDb()
{
    return  MV1_DbAlarm::bulid();
}

/**
 * @brief 初始化表格
 */
void MV1_LogAlarmWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "MPDUV1 " + tr("报警日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
              << tr("相数") << tr("项目") << tr("内容");
    model->setHeaders(mHeadList);
}
