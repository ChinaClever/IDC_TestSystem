#ifndef LINECHART_H
#define LINECHART_H

#include <QtCore>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

class LineChart : public QWidget
{
    Q_OBJECT
public:
    explicit LineChart(QWidget *parent = nullptr);

    void setTitle(const QString &title);
    void append(qreal y);
    void clearChart();

protected:
    void initAxisX();
    void initAxisY();
    void initAxisXTime();

    void setAxisXRange();
    void setAxisYRange(int value);

private:
    QChart *mChart;
    QSplineSeries *mSeries;
    QChartView *mChartView;

    int mY;
    QDateTime mYtime;
};

#endif // LINECHART_H
