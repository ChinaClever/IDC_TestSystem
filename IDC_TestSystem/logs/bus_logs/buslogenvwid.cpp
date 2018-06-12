#include "buslogenvwid.h"

BusLogEnvWid::BusLogEnvWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

/**
     * @brief 获取表对象
     * @return
     */
BasicSql *BusLogEnvWid::getDb()
{
    return  BusDbEnv::bulid();
}

/**
     * @brief 初始化表格
     */
void BusLogEnvWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "BUS " + tr("传感器日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("母线")
              << tr("插接箱") << tr("传感器") << tr("温度") << tr("温度下限") << tr("温度上限");
    model->setHeaders(mHeadList);
}

