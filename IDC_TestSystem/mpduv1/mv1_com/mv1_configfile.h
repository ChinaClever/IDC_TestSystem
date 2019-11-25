#ifndef MV1_CONFIGFILE_H
#define MV1_CONFIGFILE_H
#include "configbase.h"

class MV1_ConfigFile : public ConfigBase
{
    MV1_ConfigFile();
public:
    static MV1_ConfigFile *bulid();
    QString getPrefix(){return "mv1";}
};

#endif // MV1_CONFIGFILE_H
