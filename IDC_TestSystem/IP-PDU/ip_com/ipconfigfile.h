#ifndef IPCONFIGITEM_H
#define IPCONFIGITEM_H
#include "configbase.h"

class IP_ConfigFile : public ConfigBase
{
    IP_ConfigFile();
public:
    static IP_ConfigFile *bulid();
    QString getPrefix(){return "ip";}
};

#endif // IPCONFIGITEM_H
