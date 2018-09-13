#ifndef IN_MAINWID_H
#define IN_MAINWID_H

#include "in_tablewid/in_inputthresholdtablewid.h"
#include "in_set/in_setmainwid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"

namespace Ui {
class IN_MainWid;
}

class IN_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit IN_MainWid(QWidget *parent = 0);
    ~IN_MainWid();

protected:
    void initWidget();

public slots:
    void updateWidSlot(int);

private slots:
    void initFunSLot();

private:
    Ui::IN_MainWid *ui;

    IN_InputTableWid *mInputTableWid;
    IN_InputThresholdTableWid *mInputThresholdTableWid;
    TransTableWid *mTransTableWid;
    IN_EnvTableWid *mEnvTableWid;
    IN_setMainWid *mSetMainWid;
};

#endif // IN_MAINWID_H
