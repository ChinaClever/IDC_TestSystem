#include "rset_linewid.h"
#include "ui_rset_linewid.h"

RSet_LineWid::RSet_LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_LineWid)
{
    ui->setupUi(this);
    initWid();
}

RSet_LineWid::~RSet_LineWid()
{
    delete ui;
}
void RSet_LineWid::initWid()
{
    int id = 0;
    mWid[id] = new RSet_LineUnitWid(ui->volGroup);
    mWid[id++]->initWid(1, Rpdu_Rtu_Test_min);

    mWid[id] = new RSet_LineUnitWid(ui->curGroup);
    mWid[id++]->initWid(0, Rpdu_Rtu_Test_min);

    mSnmp = new RSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new RSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}

void RSet_LineWid::sendSnmp(int addr)
{
    QList<sSnmpSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(i , addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mSnmp->setCmd(list.at(i));
    }
}

void RSet_LineWid::sendRtu(int addr)
{
    QList<sRtuSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mRtu->setCmd(list.at(i));
    }
}

void RSet_LineWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void RSet_LineWid::on_pushButton_clicked()
{
    int addr = ui->spinBox->value();

    sConfigItem *item = R_ConfigFile::bulid()->item;
    if(item->setMode == Test_SNMP)
    {
        sendSnmp(addr);
    }
    else
    {
        sendRtu(addr);
    }
    mSnmp->start();
    mRtu->start();
    ui->textEdit->clear();
}
