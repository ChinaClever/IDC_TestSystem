#include "ztest_envwid.h"
#include "ui_ztest_envwid.h"

ZTest_EnvWid::ZTest_EnvWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_EnvWid)
{
    ui->setupUi(this);
    initWid();
}

ZTest_EnvWid::~ZTest_EnvWid()
{
    delete ui;
}
void ZTest_EnvWid::initWid()
{
    int id = 0;
    mWid[id] = new ZTest_EnvUnitWid(ui->temGroup);
    mWid[id++]->initWid(0, Zpdu_Rtu_Test_min);

    mWid[id] = new ZTest_EnvUnitWid(ui->humGroup);
    mWid[id++]->initWid(1, Zpdu_Rtu_Test_min);

    mRtu = new ZSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void ZTest_EnvWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void ZTest_EnvWid::on_pushButton_clicked()
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
