#include "ztest_linewid.h"
#include "ui_ztest_linewid.h"

ZTest_LineWid::ZTest_LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_LineWid)
{
    ui->setupUi(this);
    initWid();
}

ZTest_LineWid::~ZTest_LineWid()
{
    delete ui;
}
void ZTest_LineWid::initWid()
{
    int id = 0;
    mWid[id] = new ZTest_LineUnitWid(ui->volGroup);
    mWid[id++]->initWid(1, Zpdu_Rtu_Test_min);

    mWid[id] = new ZTest_LineUnitWid(ui->curGroup);
    mWid[id++]->initWid(0, Zpdu_Rtu_Test_min);


    mRtu = new ZTest_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void ZTest_LineWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void ZTest_LineWid::on_pushButton_clicked()
{
    QList<sRtuSetCmd> list;
    int addr = ui->spinBox->value();

    for(int i=0; i<2; ++i) {
       mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
         mRtu->setCmd(list.at(i));
    }

    mRtu->start();
    ui->textEdit->clear();
}
