#ifndef M_CONFIGFILE_H
#define M_CONFIGFILE_H
#include "configbase.h"

enum {
    M_Test_Stop,
    M_Test_Simulate,  // 模拟测试
    M_Test_Function, // 功能测试

    M_Info_Dev, // 母线信息
    M_Info_Trans, // Modbus传输统计实时显示界面
    M_Info_Threshold, // 设备阈值实时显示界面
    M_Info_Env, // 环境信息_
    M_Info_Output,
    M_Info_OutputThreshold,
    M_Info_Set,

    M_Log_Modbus, // Modbus日志界面
    M_Log_Trans, // Modbus 传输日志
    M_Log_Env,  //设备环境日志
    M_Log_Records, // 设备纪录日志
    M_Log_Threshold, // 设备阈值日志
    M_Log_Output,
    M_Log_Alarm,
};


struct sM_ConfigItem
{
    sM_ConfigItem() {testMode=0; msecs = 5; logMins=60;}

    int testMode; // 测试模式
    int msecs;
    int logMins; // 日志间隔时间分钟

    SerialPort *serial; // 串口对象
    int devNum; // 级联数
    int cmdModel; // 命令模式
    int outputNum;
};


class M_ConfigFile : public ConfigBase
{
    M_ConfigFile();
public:
    static M_ConfigFile *bulid();

    sM_ConfigItem *item;
    QString getPrefix(){return "m";}
};

#endif // M_CONFIGFILE_H
