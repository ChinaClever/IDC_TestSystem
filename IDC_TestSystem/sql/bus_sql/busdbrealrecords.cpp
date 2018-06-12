#include "busdbrealrecords.h"

BusDbRealRecords::BusDbRealRecords()
{
    createTable();
}


BusDbRealRecords *BusDbRealRecords::bulid()
{
    static BusDbRealRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new BusDbRealRecords();
    return sington;
}

void BusDbRealRecords::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "bus            VCHAR,"
            "box            VCHAR,"
            "loop           VCHAR,"
            "sw_str         VCHAR,"
            "vol            DOUBLE,"
            "cur            DOUBLE,"
            "pow            DOUBLE,"
            "apow           DOUBLE,"
            "pf             DOUBLE,"
            "ele            DOUBLE);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}


bool BusDbRealRecords::insertItem(BusDbRealRecordItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, bus, box, loop, sw_str, vol, cur, pow, apow, pf, ele) "
                  "values(:id,:date,:time,:bus,:box,:loop,:sw_str,:vol,:cur,:pow,:apow,:pf,:ele)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool BusDbRealRecords::modifyItem(const BusDbRealRecordItem &item, const QString &cmd)
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
    query.bindValue(":sw_str",item.sw_str);
    query.bindValue(":vol",item.vol);
    query.bindValue(":cur",item.cur);
    query.bindValue(":pow",item.pow);
    query.bindValue(":apow",item.apow);
    query.bindValue(":pf",item.pf);
    query.bindValue(":ele",item.ele);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void BusDbRealRecords::selectItem(QSqlQuery &query, BusDbRealRecordItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.bus = query.value("bus").toString();
    item.box = query.value("box").toString();
    item.loop = query.value("loop").toString();
    item.sw_str = query.value("sw_str").toString();
    item.vol = query.value("vol").toDouble();
    item.cur = query.value("cur").toDouble();
    item.pow = query.value("pow").toDouble();
    item.apow = query.value("apow").toDouble();
    item.pf = query.value("pf").toDouble();
    item.ele = query.value("ele").toDouble();
}
