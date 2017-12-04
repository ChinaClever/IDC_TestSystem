#ifndef SICONFIGFILE_H
#define SICONFIGFILE_H
#include "serialport.h"

enum {
    SI_Test_Stop,
    SI_Test_Simulate,  // 模拟测试
    SI_Test_Function, // 功能测试

    SI_DevReal_Info,
    SI_Trans_Info,
    SI_Threshold_Info,
    SI_Env_Info, // 环境信息_

    SI_Log_Modbus, // Modbus日志界面
    SI_Log_Trans,
    SI_Log_Env,
};


struct SiConfigItem
{
    SiConfigItem() {testMode=SI_Test_Stop; msecs = 5; logMins=60;}

    int testMode; // 测试模式
    int msecs;
    int logMins; // 日志间隔时间分钟

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
