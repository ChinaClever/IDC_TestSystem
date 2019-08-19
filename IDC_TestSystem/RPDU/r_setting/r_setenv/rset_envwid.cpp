#include "rset_envwid.h"
#include "ui_rset_envwid.h"

RSet_EnvWid::RSet_EnvWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_EnvWid)
{
    ui->setupUi(this);
    initWid();
}

RSet_EnvWid::~RSet_EnvWid()
{
    delete ui;
}
void RSet_EnvWid::initWid()
{
    int id = 0;
    mWid[id] = new RSet_EnvUnitWid(ui->temGroup);
    mWid[id++]->initWid(0, Rpdu_Rtu_Test_min);

    mWid[id] = new RSet_EnvUnitWid(ui->humGroup);
    mWid[id++]->initWid(1, Rpdu_Rtu_Test_min);

    mSnmp = new RSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new RSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void RSet_EnvWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void RSet_EnvWid::sendSnmp(int addr)
{
    QList<sSnmpSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(i , addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mSnmp->setCmd(list.at(i));
    }
}

void RSet_EnvWid::sendRtu(int addr)
{
    QList<sRtuSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mRtu->setCmd(list.at(i));
    }
}

void RSet_EnvWid::on_pushButton_clicked()
{
    int addr = ui->spinBox->value();
    sConfigItem *item = R_ConfigFile::bulid()->item;
    if(item->setMode == Test_SNMP)
    {
       //sendSnmp(addr);
    }
    else
    {
       sendRtu(addr);
    }
    mSnmp->start();
    mRtu->start();
    ui->textEdit->clear();
}
