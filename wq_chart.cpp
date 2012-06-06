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
    agregarEtiquetaX(x);
    agregarEtiquetaY(y);
}

void WQ_Chart::agregarEtiquetaX(QString x)
{
    setAxisTitle(QwtPlot::xBottom, x);
}

void WQ_Chart::agregarEtiquetaY(QString y)
{
    setAxisTitle(QwtPlot::yLeft, y);
}
