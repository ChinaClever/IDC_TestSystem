#ifndef BUS_CONFIGFILE_H
#define BUS_CONFIGFILE_H
#include "configbase.h"

enum {
    BUS_Test_Stop,
    BUS_Test_Simulate,  // 模拟测试
    BUS_Test_Function, // 功能测试

    BUS_Info_Bus, // 母线信息
    BUS_Info_Box, // 接插箱信息
    BUS_Info_Loop, // 接插箱信息
    BUS_Info_Trans, // Modbus传输统计实时显示界面
    BUS_Info_Threshold, // 设备阈值实时显示界面
    BUS_Info_Env, // 环境信息_
    BUS_Info_Set,

    BUS_Log_Modbus, // Modbus日志界面
    BUS_Log_Trans, // Modbus 传输日志
    BUS_Log_Env,  //设备环境日志
    BUS_Log_Records, // 设备纪录日志
    BUS_Log_Threshold, // 设备阈值日志
    BUS_Log_Alarm,
};


struct BusConfigItem
{
    BusConfigItem() {testMode=0; msecs = 5; logMins=60;}

    int testMode; // 测试模式
    int msecs;
    int logMins; // 日志间隔时间分钟

    SerialPort *serial; // 串口对象
    int lineNum; // 相数
    int devNum; // 级联数
    int cmdModel; // 命令模式
};


class BUS_ConfigFile : public ConfigBase
{
    BUS_ConfigFile();
public:
    static BUS_ConfigFile *bulid();

    BusConfigItem *item;
    QString getPrefix(){return "bus";}
};

#endif // BUS_CONFIGFILE_H
