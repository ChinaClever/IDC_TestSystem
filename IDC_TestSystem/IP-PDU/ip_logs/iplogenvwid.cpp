/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "iplogenvwid.h"
#include "ip_sql/ipdbenv.h"

IpLogEnvWid::IpLogEnvWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *IpLogEnvWid::getDb()
{
    return  IpDbEnv::bulid();
}

/**
 * @brief 初始化表格
 */
void IpLogEnvWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "IP " + tr("传感器日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号") << tr("传感顺")
              << tr("温度") << tr("温度下限") << tr("温度上限")
              << tr("湿度") << tr("湿度下限") << tr("湿度上限") ;
    model->setHeaders(mHeadList);
}

