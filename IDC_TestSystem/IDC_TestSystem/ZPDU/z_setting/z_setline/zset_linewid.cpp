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

    mSnmp = new ZSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new ZSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}

void ZSet_LineWid::sendSnmp(int addr)
{
    QList<sSnmpSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(i , addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mSnmp->setCmd(list.at(i));
    }
}

void ZSet_LineWid::sendRtu(int addr)
{
    QList<sRtuSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mRtu->setCmd(list.at(i));
    }
}

void ZSet_LineWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void ZSet_LineWid::on_pushButton_clicked()
{
    int addr = ui->spinBox->value();

    sConfigItem *item = Z_ConfigFile::bulid()->item;
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
