#ifndef LOOPTABLEWID_H
#define LOOPTABLEWID_H

#include "outputtablewid.h"

class LoopTableWid : public OutputTableWid
{
    Q_OBJECT
public:
    explicit LoopTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    int updateDev(sDataPacket *dev, int row);
    double autoRate(int vol);
};

#endif // LOOPTABLEWID_H
