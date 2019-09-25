/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "busdbenv.h"

BusDbEnv::BusDbEnv()
{    
    createTable();
}


BusDbEnv *BusDbEnv::bulid()
{
    static BusDbEnv* sington = nullptr;
    if(sington == nullptr)
        sington = new BusDbEnv();
    return sington;
}

void BusDbEnv::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "bus            VCHAR,"
            "box            VCHAR,"
            "loop           VCHAR,"
            "tem            INTEGER,"
            "tem_min        INTEGER,"
            "tem_max        INTEGER);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}


bool BusDbEnv::insertItem(BusDbEnvItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, bus, box, loop, tem, tem_min, tem_max) "
                  "values(:id,:date,:time,:bus,:box,:loop,:tem,:tem_min,:tem_max)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool BusDbEnv::modifyItem(const BusDbEnvItem &item, const QString &cmd)
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
    query.bindValue(":tem",item.tem);
    query.bindValue(":tem_min",item.tem_min);
    query.bindValue(":tem_max",item.tem_max);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void BusDbEnv::selectItem(QSqlQuery &query, BusDbEnvItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.bus = query.value("bus").toString();
    item.box = query.value("box").toString();
    item.loop = query.value("loop").toString();
    item.tem = query.value("tem").toInt();
    item.tem_min = query.value("tem_min").toInt();
    item.tem_max = query.value("tem_max").toInt();
}

