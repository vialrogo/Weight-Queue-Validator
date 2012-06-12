#ifndef WQ_CHART_H
#define WQ_CHART_H

#include <qwt_plot_curve.h>
#include <qwt_plot.h>
#include <qwt_series_data.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_canvas.h>

class WQ_Chart: public QwtPlot
{
    Q_OBJECT

private:
    QVector<QwtPlotCurve*>* vectorCurvas;
    QVector<QVector<QPointF>* >* vectorDatosCurvas;
    QwtPlotMagnifier* magnifier;
    QwtPlotPanner* panner;

public:
    WQ_Chart(QWidget* parent, QSize tamano);
    ~WQ_Chart();
    void agregarCurva(QVector<QPointF>* datos);
    void agregarEtiquetas(QString x, QString y);
    void agregarEtiquetaX(QString x);
    void agregarEtiquetaY(QString y);

public slots:
    void elimiarCurvaPlot(int numCurva);
    void mostrarOcultarCurva(int numCurva, bool estado);
};

#endif // WQ_CHART_H
