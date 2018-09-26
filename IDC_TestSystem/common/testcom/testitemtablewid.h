#ifndef TESTITEMTABLEWID_H
#define TESTITEMTABLEWID_H
#include "testitems.h"


class TestItemTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit TestItemTableWid(QWidget *parent = nullptr);

public slots:
    void startSlot(int devId);

protected:
    void initWid();
    void updateWid(sDataPacket &packet);
    void appendItem(const sTestItem &item);

private:
    TestItems *mTestItems;
};

#endif // TESTITEMTABLEWID_H
