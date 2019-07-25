#include "rset_loopwid.h"
#include "ui_rset_loopwid.h"

RSet_LoopWid::RSet_LoopWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_LoopWid)
{
    ui->setupUi(this);
    initWid();
}

RSet_LoopWid::~RSet_LoopWid()
{
    delete ui;
}
void RSet_LoopWid::initWid()
{


    mWid = new RSet_LoopUnitWid(ui->curGroup);
    mWid->initWid(Rpdu_Rtu_Test_min);

    mSnmp = new RSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new RSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void RSet_LoopWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void RSet_LoopWid::sendSnmp(int addr)
{
    QList<sSnmpSetCmd> list;
    mWid->getCmdList(addr, list);

    for(int i=0; i<list.size(); ++i) {
         mSnmp->setCmd(list.at(i));
    }
}

void RSet_LoopWid::sendRtu(int addr)
{
    QList<sRtuSetCmd> list;
    mWid->getCmdList(addr, list);

    for(int i=0; i<list.size(); ++i) {
         mRtu->setCmd(list.at(i));
    }
}

void RSet_LoopWid::on_pushButton_clicked()
{

    int addr = ui->spinBox->value();
    sConfigItem *item = R_ConfigFile::bulid()->item;
    if(item->setMode == Test_SNMP) {
        sendSnmp(addr);
    } else {
        sendRtu(addr);
    }

    mSnmp->start();
    mRtu->start();
    ui->textEdit->clear();
}
