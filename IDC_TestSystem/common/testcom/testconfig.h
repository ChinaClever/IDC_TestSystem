#ifndef TESTCONFIGFILE_H
#define TESTCONFIGFILE_H
#include "common.h"

struct sSerialNumItem
{
    QString name;
    QString op; // 操作员
    QString cn; // 电脑号
    QString sn; // 产品条码

    QString barCode; // 工状条码
    QString batch; // 批次
    QString purpose;
    QDate date;

    int spec; // 产品系列
    int line;
    int loop;
    int output;

    bool snClear;
    bool errStop;
    bool isSave;
    bool isDelayBreaker;
};

struct sTestProgress
{
    sTestProgress() {okNum=errNum=finishNum=0; allNum=10;}

    int allNum;
    int okNum;
    int errNum;
    int finishNum;
    QString status;
    QTime startTime, endTime;
};



/**
 * @brief 测试数据结构体
 */
struct sTestDataItem
{
    sTestDataItem(){id=0;}

    int id;
    bool status; // 状态

    QString item; // 检查项目
    QString subItem; // 测试项目描述

    QString expect; // 期望值
    QString measured; // 实测值
    QString result; // 结果
};

struct sTestConfigItem
{
    sTestConfigItem() {mode=0; devId=1;}

    int devId;
    int mode;
    bool isSnmp;
    sSerialNumItem serialNum;
    sTestProgress progress;

    QList<sTestDataItem> dataItem;
    QList<QStringList> logList;
    QList<sTestDataItem> logItems;
};

class TestConfig
{
public:
    TestConfig();

    sTestConfigItem *item;
    void initConfig(sSerialNumItem *it=nullptr);
    void saveConfig(sSerialNumItem *it=nullptr);

protected:
    void setSpec(int value);
    int getSpec();

    void setLine(int value);
    int getLine();

    void setLoop(int value);
    int getLoop();

    void setOutput(int value);
    int getOutput();

    QString getOp();
    void setOp(const QString &arg);

    QString getCn();
    void setCn(const QString &arg);

    QString getBarCode();
    void setBarCode(const QString &arg);

    QString getBatch();
    void setBatch(const QString &arg);

    QString getPurpose();
    void setPurpose(const QString &arg);

    bool getSnClear();
    void setSnClear(bool mode);

    bool getDelayBreaker();
    void setDelayBreaker(bool mode);

    virtual QString getPrefix()=0;
};

#endif // TESTCONFIGFILE_H
