#ifndef SI_DEVTABLEWID_H
#define SI_DEVTABLEWID_H

#include "si_transtablewid.h"

class SI_DevTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit SI_DevTableWid(QWidget *parent = nullptr);


protected:
    void initWid();

    void setDevName(int row, int column, int id);
    void setLine(int row, int column, int id, int line);
    void setSw(int row, int column, int id, int line);
    void setVolValue(int row, int column, int id, int line);
    void setCurValue(int row, int column, int id, int line);

    void setPow(int row, int column, int id, int line);
    void setActivePow(int row, int column, int id, int line);
    void setPf(int row, int column, int id, int line);
    void setEle(int row, int column, int id, int line);

    void checkRowCount();
    void updateData();
    SI_Rtu_Recv *getPacket(int id);

protected slots:
    void timeoutDone();

private:
    QTimer *timer;
};

#endif // SI_DEVTABLEWID_H
