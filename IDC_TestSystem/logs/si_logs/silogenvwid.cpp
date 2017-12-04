#include "silogenvwid.h"
#include "si_sql/sidbenv.h"

SiLogEnvWid::SiLogEnvWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}


BasicSql *SiLogEnvWid::getDb()
{
    return  SiDbEnv::bulid();
}


void SiLogEnvWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "SI" + tr("传感器日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
              << tr("温度") << tr("温度下限") << tr("温度上限")
              << tr("湿度") << tr("湿度下限") << tr("湿度上限") ;
    model->setHeaders(mHeadList);
}

