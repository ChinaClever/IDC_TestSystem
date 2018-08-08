#ifndef DPSAVELINETHRESHOLD_H
#define DPSAVELINETHRESHOLD_H

#include "dpalarmsave.h"

class DpSaveLineThreshold : public DpSaveRecord
{
    Q_OBJECT
public:
    explicit DpSaveLineThreshold(QObject *parent = nullptr);

protected:
    void saveLogItem(int id);
    virtual void insertItem(DbLineThresholdItem &item)=0;

};

#endif // DPSAVELINETHRESHOLD_H
