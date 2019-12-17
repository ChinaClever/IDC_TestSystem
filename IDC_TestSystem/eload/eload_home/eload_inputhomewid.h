#ifndef ELOAD_INPUTHOMEWID_H
#define ELOAD_INPUTHOMEWID_H

#include <QWidget>
#include "eload_inputunitwid.h"
namespace Ui {
class ELoad_InputHomeWid;
}

class ELoad_InputHomeWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_InputHomeWid(QWidget *parent = 0);
    ~ELoad_InputHomeWid();

protected:
    void initWid();
signals:
    void sendResFinishSig();
private slots:
    void updateIndexSlot(int index, QString str);
    void recvResistanceCmdSlot(int start,int end,int value);
    void timeoutDone();

private:
    Ui::ELoad_InputHomeWid *ui;
    QList<ELoad_InputUnitWid*> mListPointer;
    QTimer *timer;
    ELoad_RtuSent *mRtu;
};

#endif // ELOAD_INPUTHOMEWID_H
