#ifndef RSET_THRESHOLDITEMWID_H
#define RSET_THRESHOLDITEMWID_H

#include "../r_setsw/rset_swwid.h"
#include <QWidget>
enum{
    Rpdu_Rtu_Test_min,
    Rpdu_Rtu_Test_max,
    Rpdu_Rtu_Test_crMin,
    Rpdu_Rtu_Test_crMax,
};

namespace Ui {
class RSet_ThresholdItemWid;
}

class RSet_ThresholdItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_ThresholdItemWid(QWidget *parent = 0);
    ~RSet_ThresholdItemWid();
    void initEnv(int id, int mode);
    void initLine(int id, int mode);
    void initLoop(int id);
    void initOutput(int id, int mode);

    void setSelect(bool checked);
    void setValue(int value);

    bool select();
    int status();

protected:
    QString getStr(int mode);

private slots:
    void on_spinBox_valueChanged(int arg1);



private:
    Ui::RSet_ThresholdItemWid *ui;
    int mRate;
};

#endif // RSET_THRESHOLDITEMWID_H
