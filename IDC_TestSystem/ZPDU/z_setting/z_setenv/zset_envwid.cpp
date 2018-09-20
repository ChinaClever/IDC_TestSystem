#include "zset_envwid.h"
#include "ui_zset_envwid.h"

ZSet_EnvWid::ZSet_EnvWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_EnvWid)
{
    ui->setupUi(this);
    initWid();
}

ZSet_EnvWid::~ZSet_EnvWid()
{
    delete ui;
}
void ZSet_EnvWid::initWid()
{
    int id = 0;
    mWid[id] = new ZSet_EnvUnitWid(ui->temGroup);
    mWid[id++]->initWid(0, Zpdu_Rtu_Test_min);

    mWid[id] = new ZSet_EnvUnitWid(ui->humGroup);
    mWid[id++]->initWid(1, Zpdu_Rtu_Test_min);

    mRtu = new ZSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void ZSet_EnvWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void ZSet_EnvWid::on_pushButton_clicked()
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
