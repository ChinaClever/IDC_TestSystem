/*
 * 命令数据表
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sidbmodbuscmd.h"

SiDbModbusCmd::SiDbModbusCmd()
{    
    createTable();
}


SiDbModbusCmd *SiDbModbusCmd::bulid()
{
    static SiDbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new SiDbModbusCmd();
    return sington;
}

void SiDbModbusCmd::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "dev_id         INTEGER,"
            "msg            VCHAR);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}

bool SiDbModbusCmd::insertItem(SiDbModbusCmdItem &item)
{
    bool ret = false;
    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, dev_id, msg) "
                  "values(:id,:date,:time,:dev_id,:msg)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool SiDbModbusCmd::modifyItem(const SiDbModbusCmdItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":dev_id",item.dev_id);
    query.bindValue(":msg",item.msg);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void SiDbModbusCmd::selectItem(QSqlQuery &query, SiDbModbusCmdItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.dev_id = query.value("dev_id").toInt();
    item.msg = query.value("msg").toString();
}
