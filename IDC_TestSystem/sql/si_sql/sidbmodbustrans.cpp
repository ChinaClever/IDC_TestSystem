/*
 * 数据库
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sidbmodbustrans.h"

SiDbModbusTrans::SiDbModbusTrans()
{
    createTable();
}


SiDbModbusTrans *SiDbModbusTrans::bulid()
{
    static SiDbModbusTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new SiDbModbusTrans();
    return sington;
}

void SiDbModbusTrans::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "dev_id         INTEGER,"
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

bool SiDbModbusTrans::insertItem(SiDbModbusTransItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, dev_id, state, all_count, ok_count, err_count) "
                  "values(:id,:date,:time,:dev_id,:state,:all_count,:ok_count,:err_count)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool SiDbModbusTrans::modifyItem(const SiDbModbusTransItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":dev_id",item.dev_id);
    query.bindValue(":state",item.state);
    query.bindValue(":all_count",item.all_count);
    query.bindValue(":ok_count",item.ok_count);
    query.bindValue(":err_count",item.err_count);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void SiDbModbusTrans::selectItem(QSqlQuery &query, SiDbModbusTransItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.dev_id = query.value("dev_id").toInt();
    item.state = query.value("state").toString();
    item.all_count = query.value("all_count").toInt();
    item.ok_count = query.value("ok_count").toInt();
    item.err_count = query.value("err_count").toInt();
}

