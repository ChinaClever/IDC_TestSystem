/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_logenvwid.h"
#include "mv1_sql/mv1_dbenv.h"

MV1_LogEnvWid::MV1_LogEnvWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *MV1_LogEnvWid::getDb()
{
    return  MV1_DbEnv::bulid();
}

/**
 * @brief 初始化表格
 */
void MV1_LogEnvWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "MPDUV1 " + tr("传感器日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号") << tr("传感器")
              << tr("温度") << tr("温度下限") << tr("温度上限")
              << tr("湿度") << tr("湿度下限") << tr("湿度上限") ;
    model->setHeaders(mHeadList);
}
