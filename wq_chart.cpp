#include "wq_chart.h"

WQ_Chart::WQ_Chart(QWidget *parent, QSize tamano) :
    QwtPlot(parent)
{
    setAutoReplot(true);
    setMinimumSize(tamano.width(),tamano.height());
    setMaximumSize(tamano.width(),tamano.height());

    panner = new QwtPlotPanner(canvas()); //Moverse con el botón izquierdo
    magnifier = new QwtPlotMagnifier(canvas()); //zoom con el scroll
    vectorCurvas = new QVector<QwtPlotCurve*>();
    vectorDatosCurvas = new QVector<QVector<QPointF>* >();

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

    while (vectorCurvas->size()>0) {
        vectorCurvas->at(0)->detach();
        delete vectorCurvas->at(0);
        vectorCurvas->remove(0);
    }
    delete vectorCurvas;

    while (vectorDatosCurvas->size()>0) {
        delete vectorDatosCurvas->at(0);
        vectorDatosCurvas->remove(0);
    }
    delete vectorDatosCurvas;
}

void WQ_Chart::agregarCurva(QVector<QPointF>* datos)
{
    QwtPointSeriesData* seriesData = new QwtPointSeriesData;
    seriesData->setSamples(*datos);

    QwtPlotCurve* nuevacurva = new QwtPlotCurve();
//    nuevacurva->setPen(QPen(QColor(Qt::white)));
    nuevacurva->attach(this);

    nuevacurva->setData(seriesData);
    vectorCurvas->push_back(nuevacurva);
    vectorDatosCurvas->push_back(datos);
}

void WQ_Chart::elimiarCurvaPlot(int numCurva)
{
    vectorCurvas->at(numCurva)->detach();

    delete vectorCurvas->at(numCurva);
    vectorCurvas->remove(numCurva);

    delete vectorDatosCurvas->at(numCurva);
    vectorDatosCurvas->remove(numCurva);

    replot();
}

void WQ_Chart::mostrarOcultarCurva(int numCurva, bool estado)
{
    if(estado)
        vectorCurvas->at(numCurva)->attach(this);
    else
        vectorCurvas->at(numCurva)->detach();

    replot();
}

void WQ_Chart::cambiarColorCuva(int numCurva, QColor colorCurva)
{
    vectorCurvas->at(numCurva)->setPen(QPen(colorCurva));
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

void WQ_Chart::desHabilitarXScroll(bool estado)
{
    magnifier->setAxisEnabled(xBottom, estado);
}

void WQ_Chart::desHabilitarYScroll(bool estado)
{
    magnifier->setAxisEnabled(yLeft, estado);
}
