#ifndef ZTEST_CONFIG_H
#define ZTEST_CONFIG_H
#include "testconfig.h"


class ZTest_Config : public TestConfig
{
    ZTest_Config();
public:
     static ZTest_Config *bulid();

     QString getPrefix(){return "ztest";}
};

#endif // ZTEST_CONFIG_H
