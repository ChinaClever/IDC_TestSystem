#ifndef RTEST_CONFIG_H
#define RTEST_CONFIG_H
#include "testconfig.h"


class RTest_Config : public TestConfig
{
    RTest_Config();
public:
     static RTest_Config *bulid();

     QString getPrefix(){return "rtest";}
};

#endif // RTEST_CONFIG_H
