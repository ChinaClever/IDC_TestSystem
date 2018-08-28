#ifndef Z_CONFIGFILE_H
#define Z_CONFIGFILE_H
#include "serialportdlg.h"

enum {
    Z_Test_Stop,
    Z_Test_Simulate,  // 模拟测试
    Z_Test_Function, // 功能测试

    Z_Info_Dev, // 母线信息
    Z_Info_Trans, // Modbus传输统计实时显示界面
    Z_Info_Threshold, // 设备阈值实时显示界面
    Z_Info_Env, // 环境信息_
    Z_Info_Loop,
    Z_Info_LoopThreshold,
    Z_Info_Output,
    Z_Info_OutputThreshold,
    Z_Info_Set,

    Z_Log_Modbus, // Modbus日志界面
    Z_Log_Trans, // Modbus 传输日志
    Z_Log_Env,  //设备环境日志
    Z_Log_Records, // 设备纪录日志
    Z_Log_Threshold, // 设备阈值日志
    Z_Log_Loop,
    Z_Log_Output,
    Z_Log_Alarm,
};


struct sZ_ConfigItem
{
    sZ_ConfigItem() {testMode=0; msecs = 5; logMins=60;}

    int testMode; // 测试模式
    int msecs;
    int logMins; // 日志间隔时间分钟

    SerialPort *serial; // 串口对象
    int devNum; // 级联数
    int cmdModel; // 命令模式
};


class Z_ConfigFile : public ConfigBase
{
    Z_ConfigFile();
public:
    static Z_ConfigFile *bulid();

    sZ_ConfigItem *item;
    QString getPrefix(){return "z";}
};

#endif // Z_CONFIGFILE_H
