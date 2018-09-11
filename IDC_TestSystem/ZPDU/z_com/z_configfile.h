#ifndef Z_CONFIGFILE_H
#define Z_CONFIGFILE_H
#include "configbase.h"

class Z_ConfigFile : public ConfigBase
{
    Z_ConfigFile();
public:
    static Z_ConfigFile *bulid();

    sConfigItem *item;
    QString getPrefix(){return "z";}
};

#endif // Z_CONFIGFILE_H
