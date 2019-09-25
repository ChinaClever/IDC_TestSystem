#ifndef BUSDBMODBUSCMD_H
#define BUSDBMODBUSCMD_H
#include "busdbmodbustrans.h"

#define BUS_DB_ModbusCmd "bus_modbus_cmd"

struct BusDbModbusCmdItem : public DbBasicItem {
    QString bus, box;
    QString msg;
};



class BusDbModbusCmd : public SqlBasic<BusDbModbusCmdItem>
{
    BusDbModbusCmd();
public:
    static BusDbModbusCmd *bulid();
    virtual QString tableName(){return QString("%1").arg(BUS_DB_ModbusCmd) ;}
    bool insertItem(BusDbModbusCmdItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const BusDbModbusCmdItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,BusDbModbusCmdItem &item);
};

#endif // BUSDBMODBUSCMD_H
