#include "wq_chart.h"

WQ_Chart::WQ_Chart(QWidget *parent, QSize tamano) :QwtPlot(parent)
{
    setAutoReplot(true);
    setMinimumSize(tamano.width(),tamano.height());
    setMaximumSize(tamano.width(),tamano.height());
}

void WQ_Chart::adicionarCurva(QString nombreCurva)
{
    QwtPlotCurve* nuevacurva = new QwtPlotCurve();
    nuevacurva->attach(this);
    hashCurvas[nombreCurva]=nuevacurva;
}

void WQ_Chart::agregarDatosACurva(QString nombreCurva, QVector<QPointF>* datos)
{
    QwtPointSeriesData* seriesData = new QwtPointSeriesData;
    seriesData->setSamples(*datos);
    hashCurvas[nombreCurva]->setData(seriesData);
}

void WQ_Chart::agregarEtiquetas(QString x, QString y)
{
    setAxisTitle(QwtPlot::xBottom, x);
    setAxisTitle(QwtPlot::yLeft, y);
}
