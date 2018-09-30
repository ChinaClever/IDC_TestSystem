#ifndef TESTITEMS_H
#define TESTITEMS_H
#include "testresultwid.h"
#include "comtablewid.h"

struct sTestItem
{
    sTestItem(){isExecute = isModubs = isSnmp = true;}

    int id;
    bool isExecute; // 是否执行
    QString item; // 检查项目
    QString subItem; // 测试项目描述
    QString eResult; // 期望结果
    bool isModubs,isSnmp; // 通讯方式
};

struct sDutSpec
{
    sDutSpec() {isSnmp = true;}
    int spec;
    int lineNum;
    int loopNum;
    int outputNum;
    bool isSnmp;
};


class TestItems : public QObject
{
public:
    TestItems();

    bool bulidItems(sDutSpec *spec, QList<sTestItem> &items);

protected:
    void communication(QList<sTestItem> &items);
    void unitItem(const QString &itemStr, int num, QList<sTestItem> &items);
    void objData(const QString &itemStr, QList<sTestItem> &items, int num);
    void outputObjData(const QString &itemStr, QList<sTestItem> &items, int num);

private:
    sDutSpec *mSpec;
    int mId;
};

#endif // TESTITEMS_H
