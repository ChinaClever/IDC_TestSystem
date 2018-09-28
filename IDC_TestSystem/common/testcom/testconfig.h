#ifndef TESTCONFIGFILE_H
#define TESTCONFIGFILE_H
#include "common.h"

enum {
    Test_Dev_Zpdu,
    Test_Dev_Mpdu,
    Test_Dev_IPpdu,
    Test_Dev_SIpdu,
    Test_Dev_SIBusBar,
    Test_Dev_IPBusBar,
};

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

    bool snClear;
    bool errStop;
    bool isSave;
};

class TestConfig
{
public:
    TestConfig();

    sSerialNumItem *serialNumitem;
    void initConfig(sSerialNumItem *item=nullptr);
    void saveConfig(sSerialNumItem *item=nullptr);

protected:
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

    virtual QString getPrefix() {return "test";}
};

#endif // TESTCONFIGFILE_H
