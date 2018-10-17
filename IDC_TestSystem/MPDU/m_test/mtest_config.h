#ifndef MTEST_CONFIG_H
#define MTEST_CONFIG_H
#include "testconfig.h"

class MTest_Config : public TestConfig
{
    MTest_Config();
public:
    static MTest_Config *bulid();
    QString getPrefix(){return "mtest";}
};

#endif // MTEST_CONFIG_H
