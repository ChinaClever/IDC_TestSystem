#ifndef TESTDATATABLEWID_H
#define TESTDATATABLEWID_H
#include "testdatasave.h"

/**
 * @brief 测试数据结构体
 */
struct sTestDataItem
{
    sTestItem test; // 测试项目
    sTestDataItem(){id=0;}

    int id;
    bool status; // 状态
    QString expect; // 期望值
    QString measured; // 实测值
    QString result; // 结果
};

class TestDataTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit TestDataTableWid(QWidget *parent = nullptr);

    int getList(QList<QStringList> &list);
public slots:
    void startSLot();
    void overSLot();
    void appendItem(const sTestDataItem &item);

protected:
    void initWid();

private:
    QList<QStringList>  mList;
};

#endif // TESTDATATABLEWID_H
