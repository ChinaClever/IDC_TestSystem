#ifndef LOOPTHRESHOLDTABLEWID_H
#define LOOPTHRESHOLDTABLEWID_H

#include "outputthresholdtablewid.h"

class LoopThresholdTableWid : public OutputThresholdTableWid
{
    Q_OBJECT
public:
    explicit LoopThresholdTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    int updateDev(sDataPacket *dev, int row);
};

#endif // LOOPTHRESHOLDTABLEWID_H
