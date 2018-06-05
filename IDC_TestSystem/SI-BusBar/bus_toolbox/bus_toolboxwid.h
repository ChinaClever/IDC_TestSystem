#ifndef BUS_TOOLBOXWID_H
#define BUS_TOOLBOXWID_H

#include "common.h"

namespace Ui {
class BUS_ToolBoxWid;
}

class BUS_ToolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_ToolBoxWid(QWidget *parent = 0);
    ~BUS_ToolBoxWid();

private:
    Ui::BUS_ToolBoxWid *ui;
};

#endif // BUS_TOOLBOXWID_H
