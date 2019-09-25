#include "eload_logmodbustranswid.h"
#include "ELoad_sql/ELoad_dbmodbustrans.h"

ELoad_LogModbusTransWid::ELoad_LogModbusTransWid(QWidget *parent) : LogComWid(parent)
{
    setStretch();
}

BasicSql *ELoad_LogModbusTransWid::getDb()
{
    return  ELoad_DbModbusTrans::bulid();
}


void ELoad_LogModbusTransWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输统计日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")
                 << tr("状态") << tr("总次数") << tr("成功次数") << tr("失败次数");
    model->setHeaders(mHeadList);
}
