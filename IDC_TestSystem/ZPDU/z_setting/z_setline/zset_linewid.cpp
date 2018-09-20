#include "zset_linewid.h"
#include "ui_zset_linewid.h"

ZSet_LineWid::ZSet_LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_LineWid)
{
    ui->setupUi(this);
    initWid();
}

ZSet_LineWid::~ZSet_LineWid()
{
    delete ui;
}
void ZSet_LineWid::initWid()
{
    int id = 0;
    mWid[id] = new ZSet_LineUnitWid(ui->volGroup);
    mWid[id++]->initWid(1, Zpdu_Rtu_Test_min);

    mWid[id] = new ZSet_LineUnitWid(ui->curGroup);
    mWid[id++]->initWid(0, Zpdu_Rtu_Test_min);


    mRtu = new ZSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void ZSet_LineWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void ZSet_LineWid::on_pushButton_clicked()
{
    QList<sZTestRtuSetCmd> list;
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
