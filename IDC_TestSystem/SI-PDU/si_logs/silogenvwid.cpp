/*
 * 传感器日志显示类
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "silogenvwid.h"
#include "si_sql/sidbenv.h"

SiLogEnvWid::SiLogEnvWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

/**
 * @brief 获取表对象
 * @return
 */
BasicSql *SiLogEnvWid::getDb()
{
    return  SiDbEnv::bulid();
}

/**
 * @brief 初始化表格
 */
void SiLogEnvWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "SI " + tr("传感器日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
              << tr("温度") << tr("温度下限") << tr("温度上限")
              << tr("湿度") << tr("湿度下限") << tr("湿度上限") ;
    model->setHeaders(mHeadList);
}

