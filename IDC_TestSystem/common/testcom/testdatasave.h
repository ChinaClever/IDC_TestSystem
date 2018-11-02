#ifndef TESTDATASAVE_H
#define TESTDATASAVE_H

#include "excel_savethread.h"
#include "testitemtablewid.h"

class TestDataSave : public QObject
{
    Q_OBJECT
public:
    explicit TestDataSave(QObject *parent = nullptr);

    void init(sTestConfigItem *item) { mItem = item;}
    void saveTestData();

protected:
    int bulidHead(sSerialNumItem *item);
    int bulidProgressLog(int id, sTestProgress &arg);
    void bulidTestData(QList<QStringList> &list);

private:
    QString bulidFileName(sSerialNumItem *item);
    QString bulidPath(sSerialNumItem *item);

private:
    Excel_SaveThread *mSaveThread;
    sTestConfigItem *mItem;
    QString mFileName;
    QList<QStringList> mList;
};

#endif // TESTDATASAVE_H
