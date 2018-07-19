/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "buslogalarmwid.h"

BusLogAlarmWid::BusLogAlarmWid(QWidget *parent) : LogComWid(parent)
{

}


/**
 * @brief 获取表对象
 * @return
 */
BasicSql *BusLogAlarmWid::getDb()
{
    return  BusDbAlarm::bulid();
}

/**
 * @brief 初始化表格
 */
void BusLogAlarmWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "BUS " + tr("报警日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("母线")
              << tr("接插箱") << tr("回路") << tr("项目") << tr("内容");
    model->setHeaders(mHeadList);
}
