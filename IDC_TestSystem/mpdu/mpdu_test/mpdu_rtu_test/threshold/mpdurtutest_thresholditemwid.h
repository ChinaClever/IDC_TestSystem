#ifndef MPDURTUTEST_THRESHOLDITEMWID_H
#define MPDURTUTEST_THRESHOLDITEMWID_H

#include <QWidget>

enum{
    Mpdu_Rtu_Test_min,
    Mpdu_Rtu_Test_crMin,
    Mpdu_Rtu_Test_crMax,
    Mpdu_Rtu_Test_max,
};

namespace Ui {
class MpduRtuTest_ThresholdItemWid;
}

class MpduRtuTest_ThresholdItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_ThresholdItemWid(QWidget *parent = 0);
    ~MpduRtuTest_ThresholdItemWid();

    void init(int id, int mode);
    void setSelect(bool checked);
    void setValue(double value);

    bool select();
    int status();

protected:
    QString getStr(int mode);

private slots:
    void on_spinBox_valueChanged(double arg1);

private:
    Ui::MpduRtuTest_ThresholdItemWid *ui;
    int mRate;
};

#endif // MPDURTUTEST_THRESHOLDITEMWID_H
