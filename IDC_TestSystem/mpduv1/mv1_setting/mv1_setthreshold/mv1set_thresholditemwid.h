#ifndef MV1SET_THRESHOLDITEMWID_H
#define MV1SET_THRESHOLDITEMWID_H

#include "../mv1_setsw/mv1set_swwid.h"

enum{
    Mpdu_Rtu_Test_min,
    Mpdu_Rtu_Test_max,
    Mpdu_Rtu_Test_crMin,
    Mpdu_Rtu_Test_crMax,
    Mpdu_Rtu_Test_delay,
};


namespace Ui {
class MV1Set_ThresholdItemWid;
}

class MV1Set_ThresholdItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_ThresholdItemWid(QWidget *parent = 0);
    ~MV1Set_ThresholdItemWid();

    void initEnv(int id, int mode);
    void initLine(int id, int mode);
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
    Ui::MV1Set_ThresholdItemWid *ui;
    int mRate;
};

#endif // MV1SET_THRESHOLDITEMWID_H
