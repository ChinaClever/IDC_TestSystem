#include "eload_logalarmwid.h"
#include "ELoad_sql/ELoad_dbalarm.h"

ELoad_LogAlarmWid::ELoad_LogAlarmWid(QWidget *parent) : LogComWid(parent)
{

}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *ELoad_LogAlarmWid::getDb()
{
    return  ELoad_DbAlarm::bulid();
}

/**
 * @brief 初始化表格
 */
void ELoad_LogAlarmWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "ELoad " + tr("报警日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
              << tr("相数") << tr("项目") << tr("内容");
    model->setHeaders(mHeadList);
}
