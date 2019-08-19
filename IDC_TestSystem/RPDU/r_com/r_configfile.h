#ifndef R_CONFIGFILE_H
#define R_CONFIGFILE_H
#include "configbase.h"

class R_ConfigFile : public ConfigBase
{
    R_ConfigFile();
public:
    static R_ConfigFile *bulid();

    QString getPrefix(){return "r";}
};

#endif // R_CONFIGFILE_H
