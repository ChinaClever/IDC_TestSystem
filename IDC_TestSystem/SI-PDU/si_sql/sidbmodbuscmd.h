#ifndef SIDBMODBUSCMD_H
#define SIDBMODBUSCMD_H

#include "sql/basicsql.h"

#define SI_DB_ModbusCmd "si_modbus_cmd"

struct SiDbModbusCmdItem : public DbBasicItem {
    int dev_id;
    QString msg;
};


class SiDbModbusCmd : public SqlBasic<SiDbModbusCmdItem>
{
    SiDbModbusCmd();
public:
    static SiDbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_ModbusCmd) ;}
    bool insertItem(SiDbModbusCmdItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const SiDbModbusCmdItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,SiDbModbusCmdItem &item);
};

#endif // SIDBMODBUSCMD_H
