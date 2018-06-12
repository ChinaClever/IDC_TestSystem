#include "busdbmodbustrans.h"

BusDbModbusTrans::BusDbModbusTrans()
{    
    createTable();
}


BusDbModbusTrans *BusDbModbusTrans::bulid()
{
    static BusDbModbusTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new BusDbModbusTrans();
    return sington;
}

void BusDbModbusTrans::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "bus            VCHAR,"
            "box            VCHAR,"
            "state          VCHAR,"
            "all_count      INTEGER,"
            "ok_count       INTEGER,"
            "err_count      INTEGER);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}

bool BusDbModbusTrans::insertItem(BusDbModbusTransItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, bus, box, state, all_count, ok_count, err_count) "
                  "values(:id,:date,:time,:bus,:box,:state,:all_count,:ok_count,:err_count)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool BusDbModbusTrans::modifyItem(const BusDbModbusTransItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":bus",item.bus);
    query.bindValue(":box",item.box);
    query.bindValue(":state",item.state);
    query.bindValue(":all_count",item.all_count);
    query.bindValue(":ok_count",item.ok_count);
    query.bindValue(":err_count",item.err_count);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void BusDbModbusTrans::selectItem(QSqlQuery &query, BusDbModbusTransItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.bus = query.value("bus").toString();
    item.box = query.value("box").toString();
    item.state = query.value("state").toString();
    item.all_count = query.value("all_count").toInt();
    item.ok_count = query.value("ok_count").toInt();
    item.err_count = query.value("err_count").toInt();
}
