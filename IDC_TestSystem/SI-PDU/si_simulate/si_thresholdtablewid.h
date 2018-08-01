#ifndef SI_THRESHOLDTABLEWID_H
#define SI_THRESHOLDTABLEWID_H

#include "si_envtablewid.h"

class SI_ThresholdTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit SI_ThresholdTableWid(QWidget *parent = nullptr);

protected:
    void initWid();

    void setDevName(int row, int column, int id);
    void setLine(int row, int column, int id, int line);

    sDataUnit *getVolUnit(int id, int line);
    void setVolValue(int row, int column, int id, int line);
    void setVolMin(int row, int column, int id, int line);
    void setVolMax(int row, int column, int id, int line);

    sDataUnit *getCurUnit(int id, int line);
    void setCurValue(int row, int column, int id, int line);
    void setCurMin(int row, int column, int id, int line);
    void setCurMax(int row, int column, int id, int line);
    void updateData();

    void checkRowCount();
signals:

protected slots:
    void timeoutDone();

private:
    QTimer *timer;
};

#endif // SI_THRESHOLDTABLEWID_H
