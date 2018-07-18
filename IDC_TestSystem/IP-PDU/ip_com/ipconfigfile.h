#ifndef IPCONFIGITEM_H
#define IPCONFIGITEM_H
#include "serialportdlg.h"

enum {
    IP_Test_Stop,
    IP_Test_Simulate,  // 模拟测试
    IP_Test_Function, // 功能测试

    IP_Info_Dev, // 母线信息
    IP_Info_Trans, // Modbus传输统计实时显示界面
    IP_Info_Threshold, // 设备阈值实时显示界面
    IP_Info_Env, // 环境信息_
    IP_Info_Set,

    IP_Log_Modbus, // Modbus日志界面
    IP_Log_Trans, // Modbus 传输日志
    IP_Log_Env,  //设备环境日志
    IP_Log_Records, // 设备纪录日志
    IP_Log_Threshold, // 设备阈值日志
    IP_Log_Alarm,
};


struct IpConfigItem
{
    IpConfigItem() {testMode=0; msecs = 5; logMins=60;}

    int testMode; // 测试模式
    int msecs;
    int logMins; // 日志间隔时间分钟

    SerialPort *serial; // 串口对象
    int lineNum; // 相数
    int devNum; // 级联数
    int cmdModel; // 命令模式
    int v;
};


class IP_ConfigFile : public ConfigBase
{
    IP_ConfigFile();
public:
    static IP_ConfigFile *bulid();

    IpConfigItem *item;
    QString getPrefix(){return "ip";}

    int getVersion();
    void setVersion(int num);
};

#endif // IPCONFIGITEM_H
