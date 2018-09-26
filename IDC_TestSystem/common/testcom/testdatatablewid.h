#ifndef TESTDATATABLEWID_H
#define TESTDATATABLEWID_H

#include "testitemtablewid.h"

struct sTestDataItem
{
    sTestItem test;

    int id;
    bool status;
    QString expect;
    QString measured;
    QString result;
};

class TestDataTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit TestDataTableWid(QWidget *parent = nullptr);

    int getItems(QList<sTestDataItem> &items);
public slots:
    void startSLot();
    void appendItem(const sTestDataItem &item);

protected:
    void initWid();
private:
    QList<sTestDataItem>  mTestDataItem;
};

#endif // TESTDATATABLEWID_H
