#ifndef WQ_CHART_H
#define WQ_CHART_H

//Includes de QWT
#include <qwt_plot_curve.h>
#include <qwt_plot.h>
#include <qwt_series_data.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_canvas.h>

class WQ_Chart: public QwtPlot
{
private:
    QHash<QString, QwtPlotCurve*> hashCurvas;
    QwtPlotMagnifier* magnifier;

public:
    WQ_Chart(QWidget* parent, QSize tamano);
    void adicionarCurva(QString nombreCurva);
    void agregarDatosACurva(QString nombreCurva, QVector<QPointF>* datos);
    void agregarEtiquetas(QString x, QString y);
    void agregarEtiquetaX(QString x);
    void agregarEtiquetaY(QString y);
};

#endif // WQ_CHART_H
