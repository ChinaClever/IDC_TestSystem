#ifndef SI_ENVTABLEWID_H
#define SI_ENVTABLEWID_H

#include "comtablewid.h"
#include "si_com/sidatapackets.h"

class SI_EnvTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit SI_EnvTableWid(QWidget *parent = nullptr);

protected:
    void initWid();

    void setDevName(int id, int column);

    SI_sDataUnit *getTempUnit(int id);
    void setTempValue(int id, int column);
    void setTempMin(int id, int column);
    void setTempMax(int id, int column);

    SI_sDataUnit *getHumUnit(int id);
    void setHumValue(int id, int column);

    void setHumMin(int id, int column);
    void setHumMax(int id, int column);
    void updateData();

signals:

protected slots:
    void timeoutDone();

private:
    QTimer *timer;
};

#endif // SI_ENVTABLEWID_H
