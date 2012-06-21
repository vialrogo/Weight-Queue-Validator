#ifndef WQ_CHART_WIDGET_H
#define WQ_CHART_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QColorDialog>
#include "wq_button.h"

namespace Ui {
class WQ_Chart_Widget;
}

class WQ_Chart_Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WQ_Chart_Widget(QWidget *parent = 0, int numChart_in=0);
    ~WQ_Chart_Widget();
    void agregarCurva(QString nombreCurva);
    int getNumChart();
    int getNumeroCurvas();
    void setNumChart(int numeroChart_in);
    void cambiarGeometriaNumeroCharts(int numCharts);
    
private:
    Ui::WQ_Chart_Widget *ui;
    int numeroChart;
    QVector<QLabel*>* vectorNombres;
    QVector<WQ_Button*>* vectorBotonesColors;
    QVector<WQ_Button*>* vectorBotonesView;
    QVector<WQ_Button*>* vectorBotonesRemove;
    QVector<bool>* vectorEstadoView;
    QFont* fontNormal;
    QFont* fontHide;

public slots:
    void clickBotonEliminarChart();
    void eliminarCurvaChartWidget(int numCurva);
    void mostrarOcultarCurva(int numCurva);
    void cambiarColorCurva(int numCurva);
    void pulsoCheckboxX(int iestado);
    void pulsoCheckboxY(int iestado);

signals:
    void eliminarChart(int numeroChart);
    void eliminarCurvaChart(int numCurva);
    void mostrarOcultarCurvaChart(int numCurva, bool estado);
    void cambiarColorCurvaChart(int numCurva, QColor colorCurva);
    void cambiarScrollX(bool estado);
    void cambiarScrollY(bool estado);
};

#endif // WQ_CHART_WIDGET_H
