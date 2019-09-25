/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_logenvwid.h"
#include "r_sql/r_dbenv.h"

R_LogEnvWid::R_LogEnvWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *R_LogEnvWid::getDb()
{
    return  R_DbEnv::bulid();
}

/**
 * @brief 初始化表格
 */
void R_LogEnvWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "R-PDU " + tr("传感器日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号") << tr("传感器")
              << tr("温度") << tr("温度下限") << tr("温度上限")
              << tr("湿度") << tr("湿度下限") << tr("湿度上限") ;
    model->setHeaders(mHeadList);
}
