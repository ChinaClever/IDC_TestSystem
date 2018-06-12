#include "busdbmodbuscmd.h"

BusDbModbusCmd::BusDbModbusCmd()
{
    createTable();
}


BusDbModbusCmd *BusDbModbusCmd::bulid()
{
    static BusDbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new BusDbModbusCmd();
    return sington;
}

void BusDbModbusCmd::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "bus            VCHAR,"
            "box            VCHAR,"
            "msg            VCHAR);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}

bool BusDbModbusCmd::insertItem(BusDbModbusCmdItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, bus, box, msg) "
                  "values(:id,:date,:time,:bus,:box,:msg)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool BusDbModbusCmd::modifyItem(const BusDbModbusCmdItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":bus",item.bus);
    query.bindValue(":box",item.box);
    query.bindValue(":msg",item.msg);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void BusDbModbusCmd::selectItem(QSqlQuery &query, BusDbModbusCmdItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.bus = query.value("bus").toString();
    item.box = query.value("box").toString();
    item.msg = query.value("msg").toString();
}

