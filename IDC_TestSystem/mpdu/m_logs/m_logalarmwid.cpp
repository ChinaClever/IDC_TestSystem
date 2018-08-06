#include "m_logalarmwid.h"
#include "m_sql/m_dbalarm.h"

M_LogAlarmWid::M_LogAlarmWid(QWidget *parent) : LogComWid(parent)
{

}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *M_LogAlarmWid::getDb()
{
    return  M_DbAlarm::bulid();
}

/**
 * @brief 初始化表格
 */
void M_LogAlarmWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "M-PDU " + tr("报警日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
              << tr("相数") << tr("项目") << tr("内容");
    model->setHeaders(mHeadList);
}
