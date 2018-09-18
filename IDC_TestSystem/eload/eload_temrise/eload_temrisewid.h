#ifndef ELOAD_TEMRISEWID_H
#define ELOAD_TEMRISEWID_H

#include "linechart.h"

namespace Ui {
class ELoad_TemRiseWid;
}

class ELoad_TemRiseWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_TemRiseWid(QWidget *parent = 0);
    ~ELoad_TemRiseWid();

    void init(int id);

protected slots:
    void timeoutDone();

private:
    Ui::ELoad_TemRiseWid *ui;

    int mId;
    LineChart *mChart;
    QTimer *timer;
};

#endif // ELOAD_TEMRISEWID_H
