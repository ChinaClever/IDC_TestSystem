#include "z_logalarmwid.h"
#include "z_sql/z_dbalarm.h"

Z_LogAlarmWid::Z_LogAlarmWid(QWidget *parent) : LogComWid(parent)
{

}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *Z_LogAlarmWid::getDb()
{
    return  Z_DbAlarm::bulid();
}

/**
 * @brief 初始化表格
 */
void Z_LogAlarmWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Z-PDU " + tr("报警日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
              << tr("相数") << tr("项目") << tr("内容");
    model->setHeaders(mHeadList);
}
