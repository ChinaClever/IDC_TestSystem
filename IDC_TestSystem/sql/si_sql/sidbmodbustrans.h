#ifndef SIDBMODBUSTRANS_H
#define SIDBMODBUSTRANS_H

#include "sidbmodbuscmd.h"

#define SI_DB_ModbusTrans "si_modbus_trans"

struct SiDbModbusTransItem : public DbBasicItem {
    int dev_id;
    QString state;
    int all_count, ok_count, err_count;
};

class SiDbModbusTrans : public SqlBasic<SiDbModbusTransItem>
{
    SiDbModbusTrans();
public:
    static SiDbModbusTrans *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_ModbusTrans) ;}
    bool insertItem(SiDbModbusTransItem &item); // 插入

    void createTable();
protected:
    bool modifyItem(const SiDbModbusTransItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,SiDbModbusTransItem &item);
};

#endif // SIDBMODBUSTRANS_H
