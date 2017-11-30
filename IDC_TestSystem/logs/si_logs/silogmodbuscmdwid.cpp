#include "silogmodbuscmdwid.h"
#include "si_sql/sidbmodbuscmd.h"

SiLogModbusCmdWid::SiLogModbusCmdWid(QWidget *parent) : LogComWid(parent)
{

}


QString SiLogModbusCmdWid::getTableName()
{
    return  SiDbModbusCmd::bulid()->tableName();
}

void SiLogModbusCmdWid::initTable()
{
    QString table = getTableName();
    this->refreshTable(table);

    mTableTile = "Modbus" + tr("传输日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间") << tr("设备号")<< tr("内容") ;
    model->setHeaders(mHeadList);
}


void SiLogModbusCmdWid::clearTableSlot()
{
    model->model->setTable("markingtable");
    SiDbModbusCmd* db = SiDbModbusCmd::bulid();
    db->clear();
    db->createTable();
    initTable();
    //    if(model->removeRow(0))
    //        QTimer::singleShot(10,this,SLOT(clearTableSlot()));
}
