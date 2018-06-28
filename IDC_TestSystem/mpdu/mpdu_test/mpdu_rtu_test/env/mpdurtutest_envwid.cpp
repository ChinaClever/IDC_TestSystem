#include "mpdurtutest_envwid.h"
#include "ui_mpdurtutest_envwid.h"

MpduRtuTest_EnvWid::MpduRtuTest_EnvWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_EnvWid)
{
    ui->setupUi(this);
}

MpduRtuTest_EnvWid::~MpduRtuTest_EnvWid()
{
    delete ui;
}


void MpduRtuTest_EnvWid::initWid(SerialPort *serial)
{
    int id = 0;
    mWid[id] = new MpduRtuTest_EnvUnitWid(ui->temGroup);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_min);

    mWid[id] = new MpduRtuTest_EnvUnitWid(ui->humGroup);
    mWid[id++]->initWid(1, Mpdu_Rtu_Test_min);

    mRtu = new MpduRtuTestThread(this);
    mRtu->init(serial);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MpduRtuTest_EnvWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void MpduRtuTest_EnvWid::on_pushButton_clicked()
{
    QList<sMpduRtuTestSetCmd> list;
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
