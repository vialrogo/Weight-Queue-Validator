#include "wq_chart.h"

WQ_Chart::WQ_Chart(QWidget *parent, QSize tamano) :QwtPlot(parent)
{
    setAutoReplot(true);
    setMinimumSize(tamano.width(),tamano.height());
    setMaximumSize(tamano.width(),tamano.height());

    panner = new QwtPlotPanner(canvas()); //Moverse con el botón izquierdo
    magnifier = new QwtPlotMagnifier(canvas()); //zoom con el scroll

    //Pendiente a sacar de aquí
    magnifier->setAxisEnabled(yLeft, false); //Desabilita el scroll sobre el eje vertical

    //Canvas
    canvas()->setLineWidth(1);
    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain);
    canvas()->setBorderRadius(5);
    canvas()->setPalette(Qt::white); //Fondo del canvas
}

WQ_Chart::~WQ_Chart()
{
    delete panner;
    delete magnifier;
    foreach (QwtPlotCurve* curva, hashCurvas) {
        delete curva;
    }
}

void WQ_Chart::agregarCurva(QString nombreCurva, QVector<QPointF>* datos)
{
    QwtPointSeriesData* seriesData = new QwtPointSeriesData;
    seriesData->setSamples(*datos);

    QwtPlotCurve* nuevacurva = new QwtPlotCurve();
    nuevacurva->attach(this);

    nuevacurva->setData(seriesData);
    hashCurvas[nombreCurva]=nuevacurva;
}

void WQ_Chart::agregarEtiquetas(QString x, QString y)
{
    agregarEtiquetaX(x);
    agregarEtiquetaY(y);
}

void WQ_Chart::agregarEtiquetaX(QString x)
{
    setAxisTitle(xBottom, x);
}

void WQ_Chart::agregarEtiquetaY(QString y)
{
    setAxisTitle(yLeft, y);
}
