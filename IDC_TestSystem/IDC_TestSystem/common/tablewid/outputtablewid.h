#ifndef OUTPUTTABLEWID_H
#define OUTPUTTABLEWID_H

#include "linetablewid.h"

class OutputTableWid : public LineTableWid
{
    Q_OBJECT
public:
    explicit OutputTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    int updateDev(sDataPacket *dev, int row);
};

#endif // OUTPUTTABLEWID_H
