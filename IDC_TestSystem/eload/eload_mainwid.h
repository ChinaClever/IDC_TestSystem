#ifndef ELOAD_MAINWID_H
#define ELOAD_MAINWID_H

#include "eload_toolbox/eload_toolboxwid.h"
#include "eload_home/eload_homemainwid.h"
#include "eload_input/in_mainwid.h"

namespace Ui {
class ELoad_MainWid;
}

class ELoad_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_MainWid(QWidget *parent = 0);
    ~ELoad_MainWid();

protected slots:
    void initFunSLot();
    void toolBoxSlot(int);

private:
    Ui::ELoad_MainWid *ui;
    ELoad_ToolBoxWid *mtoolBoxWid;
    ELoad_HomeMainWid *mHomeMainWid;
    IN_MainWid *mInputMainWid;
};

#endif // ELOAD_MAINWID_H