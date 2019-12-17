#ifndef MV1TEST_CONFIG_H
#define MV1TEST_CONFIG_H
#include "testconfig.h"

class MV1Test_Config : public TestConfig
{
    MV1Test_Config();
public:
    static MV1Test_Config *bulid();
    QString getPrefix(){return "mv1test";}
};

#endif // MV1TEST_CONFIG_H
