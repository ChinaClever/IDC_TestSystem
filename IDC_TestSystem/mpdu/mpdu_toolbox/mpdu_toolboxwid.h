#ifndef MPDU_TOOLBOXWID_H
#define MPDU_TOOLBOXWID_H

#include <QWidget>

namespace Ui {
class MPDU_ToolBoxWid;
}

class MPDU_ToolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit MPDU_ToolBoxWid(QWidget *parent = 0);
    ~MPDU_ToolBoxWid();

private:
    Ui::MPDU_ToolBoxWid *ui;
};

#endif // MPDU_TOOLBOXWID_H
