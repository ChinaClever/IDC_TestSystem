#include "busdbthresholds.h"

BusDbThresholds::BusDbThresholds()
{    
    createTable();
}


BusDbThresholds *BusDbThresholds::bulid()
{
    static BusDbThresholds* sington = nullptr;
    if(sington == nullptr)
        sington = new BusDbThresholds();
    return sington;
}

void BusDbThresholds::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "bus            VCHAR,"
            "box            VCHAR,"
            "loop           VCHAR,"
            "vol            DOUBLE,"
            "vol_min        DOUBLE,"
            "vol_max        DOUBLE,"
            "cur            DOUBLE,"
            "cur_min        DOUBLE,"
            "cur_max        DOUBLE);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}


bool BusDbThresholds::insertItem(BusDbThresholdItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, bus, box, loop, vol, vol_min, vol_max, cur, cur_min, cur_max) "
                  "values(:id,:date,:time,:bus,:box,:loop,:vol,:vol_min,:vol_max,:cur,:cur_min,:cur_max)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool BusDbThresholds::modifyItem(const BusDbThresholdItem &item, const QString &cmd)
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
    query.bindValue(":vol",item.vol);
    query.bindValue(":vol_min",item.vol_min);
    query.bindValue(":vol_max",item.vol_max);
    query.bindValue(":cur",item.cur);
    query.bindValue(":cur_min",item.cur_min);
    query.bindValue(":cur_max",item.cur_max);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void BusDbThresholds::selectItem(QSqlQuery &query, BusDbThresholdItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.bus = query.value("bus").toString();
    item.box = query.value("box").toString();
    item.loop = query.value("loop").toString();
    item.vol = query.value("vol").toDouble();
    item.vol_min = query.value("vol_min").toDouble();
    item.vol_max = query.value("vol_max").toDouble();
    item.cur = query.value("cur").toDouble();
    item.cur_min = query.value("cur_min").toDouble();
    item.cur_max = query.value("cur_max").toDouble();
}
