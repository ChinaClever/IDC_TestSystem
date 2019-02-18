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


    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

ELoad_TemRiseWid::~ELoad_TemRiseWid()
{
    delete ui;
}

void ELoad_TemRiseWid::init()
{
    QString title = tr("温升");
    mChart->setTitle(title);
}

void ELoad_TemRiseWid::timeoutDone()
{
    for(int i = 0 ; i < 3 ; i++)
    {
        int tem = IN_DataPackets::bulid()->getTemRise(i+1);
        mChart->append(tem,i+1);
    }
}
