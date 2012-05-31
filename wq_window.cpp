#include "wq_window.h"
#include "ui_wq_window.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_series_data.h>

WQ_Window::WQ_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WQ_Window)
{
    ui->setupUi(this);


    //////////////////Código tomado de un ejemplo//////////////////

    QwtPlot *myPlot = new QwtPlot(ui->widgetChart2);

    QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");


    QwtPointSeriesData* myData = new QwtPointSeriesData;

    QVector<QPointF>* samples = new QVector<QPointF>;
    samples->push_back(QPointF(1.0,1.0));
    samples->push_back(QPointF(2.0,2.0));
    samples->push_back(QPointF(3.0,3.0));
    samples->push_back(QPointF(4.0,5.0));
    myData->setSamples(*samples);
    curve1->setData(myData);

    curve1->attach(myPlot);

    myPlot->replot();

    //////////////////////////////////////////////////////////////////
}

WQ_Window::~WQ_Window()
{
    delete ui;
}
