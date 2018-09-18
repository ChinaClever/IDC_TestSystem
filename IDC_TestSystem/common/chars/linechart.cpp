/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "linechart.h"

LineChart::LineChart(QWidget *parent) : QWidget(parent)
{
    mSeries = new QSplineSeries(this);
    mChart = new QChart(this);
    mChart->legend()->hide();
    mChart->addSeries(mSeries);
    mChart->createDefaultAxes();

    mChartView = new QChartView(mChart);
    mChartView->setRenderHint(QPainter::Antialiasing);

    initAxisX();
    initAxisY();
}

void LineChart::setTitle(const QString &title)
{
    mChart->setTitle(title);
}

void LineChart::initAxisY()
{
    QAbstractAxis *axis =  mChart->axisY();
    axis->setTitleText(tr("温度"));
    mX = 0; setAxisX(40);
}

void LineChart::initAxisX()
{
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("hh:mm:ss");
    axisX->setTitleText("Time");
    mChart->addAxis(axisX, Qt::AlignBottom);
    mSeries->attachAxis(axisX);

    QTime time = QTime::currentTime();
    mYtime = QTime::currentTime().addSecs(60);
    axisX->setRange(time, mYtime);
}

void LineChart::setAxisYRange(int value)
{
    int x = int (mX * 3 / 4.0);
    if(value > x)  mX = int (value * 3 / 2.0);
    mChart->axisY()->setRange(0, mX);
}

void LineChart::setAxisXRange()
{
    if(QTime::currentTime() > mYtime) mYtime = QTime::currentTime().addSecs(60);
    mChart->axisX()->setMax(mYtime);
}

void LineChart::append(qreal y)
{
    setAxisXRange();
    setAxisYRange(y);

    int x = QTime::currentTime().toMSecsSinceEpoch();
    mSeries->append(x, y);
}

void LineChart::clearChart()
{
    mSeries->clear();
}
