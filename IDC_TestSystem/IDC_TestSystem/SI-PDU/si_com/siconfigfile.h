#ifndef SICONFIGFILE_H
#define SICONFIGFILE_H
#include "configbase.h"

class SiConfigFile : public ConfigBase
{
    SiConfigFile();
public:
    static SiConfigFile *bulid();
    QString getPrefix(){return "si";}
};

#endif // SICONFIGFILE_H
