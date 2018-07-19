#include "iplogalarmwid.h"
#include "ip_sql/ipdbalarm.h"

IpLogAlarmWid::IpLogAlarmWid(QWidget *parent) : LogComWid(parent)
{

}


/**
 * @brief 获取表对象
 * @return
 */
BasicSql *IpLogAlarmWid::getDb()
{
    return  IpDbAlarm::bulid();
}

/**
 * @brief 初始化表格
 */
void IpLogAlarmWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "IP " + tr("报警日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
              << tr("相数") << tr("项目") << tr("内容");
    model->setHeaders(mHeadList);
}
