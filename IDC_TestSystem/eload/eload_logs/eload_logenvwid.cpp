#include "eload_logenvwid.h"
#include "eload_sql/eload_dbenv.h"

ELoad_LogEnvWid::ELoad_LogEnvWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *ELoad_LogEnvWid::getDb()
{
    return  ELoad_DbEnv::bulid();
}

/**
 * @brief 初始化表格
 */
void ELoad_LogEnvWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "ELoad-PDU " + tr("传感器日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号") << tr("传感器")
              << tr("温度") << tr("温度下限") << tr("温度上限")
              << tr("湿度") << tr("湿度下限") << tr("湿度上限") ;
    model->setHeaders(mHeadList);
}

