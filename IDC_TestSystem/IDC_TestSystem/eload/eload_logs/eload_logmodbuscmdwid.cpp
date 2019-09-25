#include "eload_logmodbuscmdwid.h"
#include "ELoad_sql/ELoad_dbmodbuscmd.h"

ELoad_LogModbusCmdWid::ELoad_LogModbusCmdWid(QWidget *parent) : LogComWid(parent)
{

}

BasicSql *ELoad_LogModbusCmdWid::getDb()
{
    return  ELoad_DbModbusCmd::bulid();
}

void ELoad_LogModbusCmdWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输错误日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")<< tr("内容") ;
    model->setHeaders(mHeadList);
}

