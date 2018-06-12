#ifndef BUSDBMODBUSTRANS_H
#define BUSDBMODBUSTRANS_H
#include "busdbrealrecords.h"

#define BUS_DB_ModbusTrans "bus_modbus_trans"

struct BusDbModbusTransItem : public DbBasicItem {
    QString bus, box, loop, state;
    int all_count, ok_count, err_count;
};

class BusDbModbusTrans : public SqlBasic<BusDbModbusTransItem>
{
    BusDbModbusTrans();
public:
    static BusDbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(BUS_DB_ModbusTrans) ;}
    bool insertItem(BusDbModbusTransItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const BusDbModbusTransItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,BusDbModbusTransItem &item);

};

#endif // BUSDBMODBUSTRANS_H
