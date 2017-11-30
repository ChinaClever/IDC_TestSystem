#ifndef SITOOLBOXWID_H
#define SITOOLBOXWID_H

#include <QWidget>
#include "sisimulationtoolwid.h"
#include "sitesttoolwid.h"
#include "sisettingtoolwid.h"
#include "silogstoolwid.h"

namespace Ui {
class SitoolBoxWid;
}

class SitoolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit SitoolBoxWid(QWidget *parent = 0);
    ~SitoolBoxWid();

signals:
     void toolBoxSig(int);


protected:
    void initWid();


private:
    Ui::SitoolBoxWid *ui;

    SiSimulationToolWid *mSimulationToolWid;
    SiLogsToolWid *mLogsToolWid;
    SiTestToolWid *mTestToolWid;
    SiSettingToolWid *mSettingToolWid;
};

#endif // SITOOLBOXWID_H
