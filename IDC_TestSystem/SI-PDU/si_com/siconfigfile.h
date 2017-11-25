#ifndef SICONFIGFILE_H
#define SICONFIGFILE_H
#include "serialport.h"

enum {
    SI_Test_Stop,
    SI_Test_Simulate,  // 模拟测试
    SI_Test_Function, // 功能测试
};


struct SiConfigItem
{
    SiConfigItem() {testMode=SI_Test_Stop; msecs = 5;}

    int testMode; // 测试模式
    int msecs;

    SerialPort *serial; // 串口对象
    int lineNum; // 相数
    int devNum; // 级联数
    int cmdModel; // 命令模式
};



class SiConfigFile : public ConfigBase
{
    SiConfigFile();
public:
    static SiConfigFile *bulid();

     SiConfigItem *item;
    QString getPrefix(){return "SI";}



};

#endif // SICONFIGFILE_H
