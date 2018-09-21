#ifndef ZSET_THRESHOLDITEMWID_H
#define ZSET_THRESHOLDITEMWID_H

#include "../z_setsw/zset_swwid.h"
#include <QWidget>
enum{
    Zpdu_Rtu_Test_min,
    Zpdu_Rtu_Test_max,
    Zpdu_Rtu_Test_crMin,
    Zpdu_Rtu_Test_crMax,
};

namespace Ui {
class ZSet_ThresholdItemWid;
}

class ZSet_ThresholdItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_ThresholdItemWid(QWidget *parent = 0);
    ~ZSet_ThresholdItemWid();
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
    Ui::ZSet_ThresholdItemWid *ui;
    int mRate;
};

#endif // ZSET_THRESHOLDITEMWID_H
