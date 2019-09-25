#ifndef M_CONFIGFILE_H
#define M_CONFIGFILE_H
#include "configbase.h"

class M_ConfigFile : public ConfigBase
{
    M_ConfigFile();
public:
    static M_ConfigFile *bulid();
    QString getPrefix(){return "m";}
};

#endif // M_CONFIGFILE_H
