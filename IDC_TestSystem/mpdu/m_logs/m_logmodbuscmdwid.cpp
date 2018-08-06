#include "m_logmodbuscmdwid.h"
#include "m_sql/m_dbmodbuscmd.h"

M_LogModbusCmdWid::M_LogModbusCmdWid(QWidget *parent) : LogComWid(parent)
{

}

BasicSql *M_LogModbusCmdWid::getDb()
{
    return  M_DbModbusCmd::bulid();
}

void M_LogModbusCmdWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输错误日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")<< tr("内容") ;
    model->setHeaders(mHeadList);
}
