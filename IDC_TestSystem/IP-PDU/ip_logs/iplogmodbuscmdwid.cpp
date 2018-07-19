#include "iplogmodbuscmdwid.h"
#include "ip_sql/ipdbmodbuscmd.h"

IpLogModbusCmdWid::IpLogModbusCmdWid(QWidget *parent) : LogComWid(parent)
{

}


BasicSql *IpLogModbusCmdWid::getDb()
{
    return  IpDbModbusCmd::bulid();
}

void IpLogModbusCmdWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输错误日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")<< tr("内容") ;
    model->setHeaders(mHeadList);
}
