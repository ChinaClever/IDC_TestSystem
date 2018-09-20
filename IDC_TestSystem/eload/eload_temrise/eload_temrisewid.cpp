#include "eload_temrisewid.h"
#include "ui_eload_temrisewid.h"
#include "eload_com/in_datapackets.h"

ELoad_TemRiseWid::ELoad_TemRiseWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_TemRiseWid)
{
    ui->setupUi(this);
    mChart = new LineChart(ui->widget);
    groupBox_background_icon(this);


    mId = 1;
    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

ELoad_TemRiseWid::~ELoad_TemRiseWid()
{
    delete ui;
}

void ELoad_TemRiseWid::init(int id)
{
    mId = id;

    QString title = tr("温升%1").arg(id+1);
    mChart->setTitle(title);
}

void ELoad_TemRiseWid::timeoutDone()
{
    int tem = IN_DataPackets::bulid()->getTemRise(mId);
    mChart->append(tem);
}
