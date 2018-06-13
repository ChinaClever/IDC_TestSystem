#include "busdbalarm.h"

BusDbAlarm::BusDbAlarm()
{    
    createTable();
}


BusDbAlarm *BusDbAlarm::bulid()
{
    static BusDbAlarm* sington = nullptr;
    if(sington == nullptr)
        sington = new BusDbAlarm();
    return sington;
}

void BusDbAlarm::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "bus            VCHAR,"
            "box            VCHAR,"
            "loop           VCHAR,"
            "type_str       VCHAR,"
            "msg            VCHAR);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}


bool BusDbAlarm::insertItem(BusDbAlarmItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, bus, box, loop, type_str, msg) "
                  "values(:id,:date,:time,:bus,:box,:loop,:type_str,:msg)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool BusDbAlarm::modifyItem(const BusDbAlarmItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":bus",item.bus);
    query.bindValue(":box",item.box);
    query.bindValue(":loop",item.loop);
    query.bindValue(":type_str",item.type_str);
    query.bindValue(":msg",item.msg);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void BusDbAlarm::selectItem(QSqlQuery &query, BusDbAlarmItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.bus = query.value("bus").toString();
    item.box = query.value("box").toString();
    item.loop = query.value("loop").toString();
    item.type_str = query.value("type_str").toString();
    item.msg = query.value("msg").toString();
}

