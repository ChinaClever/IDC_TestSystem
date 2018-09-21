#include "zset_loopwid.h"
#include "ui_zset_loopwid.h"

ZSet_LoopWid::ZSet_LoopWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_LoopWid)
{
    ui->setupUi(this);
    initWid();
}

ZSet_LoopWid::~ZSet_LoopWid()
{
    delete ui;
}
void ZSet_LoopWid::initWid()
{


    mWid = new ZSet_LoopUnitWid(ui->curGroup);
    mWid->initWid(Zpdu_Rtu_Test_min);


    mRtu = new ZSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void ZSet_LoopWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void ZSet_LoopWid::on_pushButton_clicked()
{
    QList<sRtuSetCmd> list;
    int addr = ui->spinBox->value();


    mWid->getCmdList(addr, list);

    for(int i=0; i<list.size(); ++i) {
         mRtu->setCmd(list.at(i));
    }

    mRtu->start();
    ui->textEdit->clear();
}
