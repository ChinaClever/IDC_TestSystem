#ifndef TESTITEMTABLEWID_H
#define TESTITEMTABLEWID_H
#include "testitems.h"


class TestItemTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit TestItemTableWid(QWidget *parent = nullptr);
    void appendItem(sTestItem &item);

protected:
    void initWid();

};

#endif // TESTITEMTABLEWID_H
