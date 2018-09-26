#ifndef TESTDATATABLEWID_H
#define TESTDATATABLEWID_H

#include "testitemtablewid.h"

struct STestDataItem
{
    sTestItem test;

    QString expect;
    QString measured;
    QString result;
};

class TestDataTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit TestDataTableWid(QWidget *parent = nullptr);

protected:
    void initWid();

signals:

public slots:
};

#endif // TESTDATATABLEWID_H
