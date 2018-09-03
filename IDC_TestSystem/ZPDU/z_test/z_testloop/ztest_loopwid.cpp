#include "ztest_loopwid.h"
#include "ui_ztest_loopwid.h"

ZTest_LoopWid::ZTest_LoopWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_LoopWid)
{
    ui->setupUi(this);
    initWid();
}

ZTest_LoopWid::~ZTest_LoopWid()
{
    delete ui;
}
void ZTest_LoopWid::initWid()
{


    mWid = new ZTest_LoopUnitWid(ui->curGroup);
    mWid->initWid(Zpdu_Rtu_Test_min);


    mRtu = new ZTest_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void ZTest_LoopWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void ZTest_LoopWid::on_pushButton_clicked()
{
    QList<sZTestRtuSetCmd> list;
    int addr = ui->spinBox->value();


    mWid->getCmdList(addr, list);

    for(int i=0; i<list.size(); ++i) {
         mRtu->setCmd(list.at(i));
    }

    mRtu->start();
    ui->textEdit->clear();
}
