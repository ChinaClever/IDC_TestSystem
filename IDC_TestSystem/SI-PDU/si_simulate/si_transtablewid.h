#ifndef SI_TRANSTABLEWID_H
#define SI_TRANSTABLEWID_H

#include "si_thresholdtablewid.h"

class SI_TransTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit SI_TransTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void updateData();

    void setDevName(int id, int column);
    void setDevState(int id, int column);

    SiDevPacket *getPacket(int id);
    void setValue(int id, int column, int value);
    void setAllValue(int id, int column);
    void setOK(int id, int column);
    void setErr(int id, int column);
signals:

public slots:
    void timeoutDone();

private:
    QTimer *timer;
};

#endif // SI_TRANSTABLEWID_H
