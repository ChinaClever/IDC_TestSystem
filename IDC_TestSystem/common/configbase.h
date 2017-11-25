#ifndef CONFIGBASE_H
#define CONFIGBASE_H
#include "sysconfigfile.h"

class ConfigBase
{
public:
    ConfigBase();

    QString getSerialName();
    void setSerialName(const QString &name);

    int getLineNum();
    void setLineNum(int num);

    int getDevNum();
    void setDevNum(int num);

    int getModbusCmd();
    void setModbusCmd(int num);

    virtual QString getPrefix()=0;
};

#endif // CONFIGBASE_H
